# UI 系统运行流程

本文件按“对象创建 -> 主题 -> 布局 -> 更新/渲染 -> 输入 -> 焦点 -> 滚动 -> 过渡动画”的顺序，解释当前 UI 系统的实际运行方式。

## 1. 创建阶段

### 1.1 所有 UI 元素都先是 `GameObject`

`UiElement` 继承自 `GameObject`，所以每个 UI 节点天然带有：

- 位置和尺寸
- 矩形缓存
- 激活与可见性
- 销毁状态
- 生命周期回调

### 1.2 `UiElement` 构造时会自动注册到主题管理器

`UiElement` 构造函数会调用：

- `UiThemeManager::instance().register_element(this)`

因此 UI 对象一创建，就被纳入主题系统的管理范围。

### 1.3 `UiControl` 在 `UiElement` 之上增加交互状态

交互控件会额外拥有：

- `_enabled`
- `_is_focused`

这两项构成键盘/手柄可操作 UI 的基础状态。

## 2. 主题应用流程

### 2.1 主题是懒刷新的

每个 `UiElement` 都有：

- `_use_theme`
- `_theme_dirty`

只有在调用 `refresh_theme_if_needed()` 且元素被标记 dirty 时，才会真正执行：

- `apply_theme(UiThemeManager::instance().current_theme())`

### 2.2 什么时候会变脏

常见触发点：

- 元素 `reset()`
- 显式调用 `mark_theme_dirty()`
- 设置新的主题角色，如按钮角色、面板角色、标签角色
- `UiThemeManager::set_theme()` 时统一把已注册元素标脏

### 2.3 主题不是强制覆盖一切

当前实现中，有些控件支持：

- 完全使用主题
- 局部使用本地配色
- 局部使用本地纹理

最典型的是 `UiButton`，它通过 `AppearanceMode` 区分这三类行为。

## 3. 布局流程

## 3.1 `UiLayout` 是主布局树

`UiLayout` 持有一组 `LayoutChild`：

- 子 `GameObject`
- 初始尺寸 `_base_size`
- 应用后的尺寸 `_applied_size`
- 本地位置 `_local_position`
- 子选项 `_options`

### 3.2 `UiLayout` 维护 dirty 标记

以下行为会触发布局脏：

- 改位置
- 改自身尺寸
- 添加/移除/清空子节点
- 改 padding / spacing / anchor / direction / cross align
- 改 transform / content offset / auto size
- 子节点被销毁

### 3.3 真正布局发生在 `apply_layout()`

`apply_layout()` 会：

1. 同步子对象当前尺寸回 `_base_size`
2. 如果开启 `auto_size`，先测内容再改自身尺寸
3. 根据方向、间距、padding、anchor、transform 计算内容起点
4. 逐个计算子元素目标位置和目标尺寸
5. 写回到每个子 `GameObject`

### 3.4 `UiLayout` 负责树状分发

在 `on_update` / `on_render` / `on_input` / `on_input_event` 中，`UiLayout` 都会：

1. 刷新主题
2. 清理已销毁子节点
3. 执行布局
4. 收集当前子对象快照
5. 逐个把生命周期回调分发给子对象

所以 `UiLayout` 同时承担：

- 排版器
- UI 树节点容器
- 生命周期传播器

### 3.5 `UiGridLayout` 是独立实现

`UiGridLayout` 没有继承 `UiLayout`，而是直接继承 `UiElement`，自己维护：

- 子列表
- 列数
- 单元格间距
- 内边距
- 横纵对齐

它适合规则网格，但功能面比 `UiLayout` 小一些。

## 4. 渲染流程

### 4.1 `UiPanel` 负责容器背景与裁剪

`UiPanel::on_render()` 的顺序是：

1. 刷新主题
2. 绘制背景纹理或背景色
3. 如开启 `_clip_children`，设置 SDL clip rect
4. 调用 `UiLayout::on_render()` 绘制子节点
5. 恢复 clip rect
6. 绘制边框

所以 `UiPanel` 的视觉职责是包裹在子内容“外层”的。

### 4.2 单体控件通常直接绘制自身

例如：

- `UiButton` 画底 + 画消息纹理
- `UiLabel` 画背景 + 画文字纹理
- `UiSlider` 画轨道条 + 画滑块 + 可选数值标签
- `UiTextInput` 画底 + 边框 + 文本 + 光标

### 4.3 文本类控件通常缓存纹理

`UiLabel`、`UiTextButton`、`UiTextInput` 都会：

- 在 dirty 时使用 `TTF_RenderUTF8_Blended*` 生成表面
- 再转换为 SDL 纹理缓存

这样正常渲染时不需要每帧重新排字。

## 5. 输入流程

## 5.1 鼠标输入走 `on_input`

典型控件：

- `UiButton`
- `UiSlider`
- `UiToggle`
- `UiScrollBar`
- `UiTextInput`

它们通常会：

1. 使用 `ui_mouse_input_allowed(input)` 判断当前帧是否接受鼠标
2. 用 `ui_logical_mouse_position()` 获取逻辑坐标
3. 用 `SDL_GetMouseState` 读按键状态
4. 自己做命中检测和按压/释放逻辑

### 5.2 键盘/手柄事件走 `handle_focused_input_event`

适合：

- 菜单上下选择
- 滑条左右调值
- 文本输入编辑
- 确认/取消

只有实现了 `UiFocusable` 的对象才能接入这套焦点式输入。

### 5.3 文本输入是事件驱动的

`UiTextInput` 的文本输入不靠轮询，而是靠：

- `InputEventType::TextInput`
- `InputAction::Backspace`
- `InputAction::DeleteKey`
- `InputAction::Home`
- `InputAction::End`

同时在获得焦点时调用 `SDL_StartTextInput()`，失焦时调用 `SDL_StopTextInput()`。

## 6. 焦点导航流程

### 6.1 焦点系统的入口是 `UiScreen`

`UiScreen` 持有：

- `_focusable_controls`
- `_focused_control_index`

并提供：

- `register_focusable_control`
- `focus_next_control`
- `focus_previous_control`
- `set_focused_control`

### 6.2 焦点不自动扫描树，而是手动注册

这点很重要：当前系统并不会遍历 UI 树自动找可聚焦对象，必须显式调用：

- `register_focusable_control(...)`

所以“是否能用键盘/手柄操作”取决于控件有没有被注册到当前 `UiScreen`。

### 6.3 焦点导航既支持鼠标选中也支持方向键切换

`UiScreen` 中：

- 鼠标按下时会检查点击到哪个 `UiFocusable`
- `Tab`、方向键会根据布局方向进行前后切换

`direction() == Horizontal` 时更偏向左右导航；
否则偏向上下导航。

## 7. 滚动流程

### 7.1 `UiScrollPanel` 自己不画滚动条

它只负责：

- 保存 `_scroll_offset`
- 根据内容尺寸计算最大滚动范围
- 在 `on_update()` 中把偏移写回 `set_content_offset`
- 响应鼠标滚轮

### 7.2 `UiScrollBar` 是独立控件

滚动条需要显式绑定目标：

- `set_target(UiScrollPanel*)`

之后通过：

- `measure_content_size()`
- `content_view_size()`
- `scroll_offset()`
- `max_scroll_offset()`

来计算 thumb 大小与位置。

### 7.3 滚动条与滚动面板是松耦合的

这很有扩展价值，因为：

- 面板可以没有滚动条
- 一个面板可以挂横向或纵向滚动条
- 滚动条可以自动跟随目标位置尺寸

## 8. 屏幕开关与过渡动画流程

### 8.1 `UiTransition` 只负责插值状态

`UiTransition` 不直接改控件，而是维护：

- hidden state
- shown state
- current state
- easing
- duration

状态内容目前包含：

- `UiLayoutTransform`
- `background_alpha`

### 8.2 `UiScreen` 把过渡状态落到自身

`UiScreen::apply_transition_state()` 会把当前过渡状态写回：

- `set_transform(...)`
- `set_background_alpha(...)`

因此过渡影响的是整个屏幕面板的位置、缩放和背景透明度。

### 8.3 打开与关闭的实际行为

`open()`：

- 设为 visible/active
- 正向播放或直接跳到 shown
- 重新同步焦点

`close()`：

- 如果开启动画，则倒放直到结束后隐藏
- 如果没开动画，则直接 invisible/inactive

## 9. 高层复合控件的工作方式

### `UiMenuList`

- 内部重建多个 `UiTextButton`
- 选中状态存在自身 `_selected_index`
- 焦点只反映到“当前项”

### `UiOptionList`

- 每一行是 `UiPanel`
- 行内再组合 `UiLabel + UiToggle/UiSlider`
- 配置变更、主题变更时可能整体重建所有行

### `UiDialog`

- 由 `UiScreen`、标题标签、消息标签、动作菜单组合而成
- 打开/关闭行为继承自 `UiScreen`
- `Cancel` 事件会尝试走取消动作，找不到则直接隐藏

## 10. 读代码时要注意的实现特征

- 很多控件的 `reset()` 会恢复默认值并重新标记主题 dirty。
- 一些 `apply_theme()` 会直接调用 `rebuild_*()`，这意味着换主题可能重建内部子树。
- `UiLabel::apply_theme()` 当前只应用颜色和背景相关字段，没有完整套用 `LabelStyle` 的对齐和 padding。
- `UiDialog` 当前虽然持有 `_action_scroll_bar`，但 `rebuild()` 没有把它加入子树，所以它不会显示出来。
- `UiOptionList::handle_row_click()` 当前没有被接入实际调用链，更像预留接口。

