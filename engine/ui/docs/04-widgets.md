# 基础控件详解

本文件说明 `widgets/` 下各基础控件与辅助器的职责、状态与实现思路。

## 1. `UiButton`

### 作用

最基础的可点击按钮控件。

### 它负责什么

- 鼠标悬停、按下、释放
- 焦点确认键激活
- 播放按下/抬起音效
- 绘制三态外观
- 支持按钮中心消息纹理
- 支持点击回调与点击计数

### 三种外观模式

- `Theme`
- `LocalColors`
- `LocalTextures`

### 重要点

- 鼠标输入通过 `on_input()` 自己轮询
- 键盘/手柄确认通过 `handle_focused_input_event()` 触发
- 主题模式下会按 `UiButtonThemeRole` 套样式

## 2. `UiTextButton`

### 作用

在 `UiButton` 之上叠加文字渲染能力。

### 实现方式

- 自己生成文本纹理
- 再把该纹理塞回 `UiButton::set_message_texture()`

### 意义

这让“按钮底图逻辑”和“按钮文字逻辑”保持分离。

## 3. `UiSelectableButton`

### 作用

支持“选中状态”的按钮，适合单选/多选列表项。

### 额外能力

- 维护 `_selected`
- 监听器订阅选中变化
- 激活时可选：
  - `Select`
  - `Toggle`

### 视觉行为

选中时，如果当前不是 `Pushed`，会把视觉状态伪装成 `Pushed`。

## 4. `UiButtonGroup`

### 作用

管理一组 `UiSelectableButton` 的单选行为。

### 职责

- 注册按钮及监听器
- 保证只有一个按钮处于选中状态
- 提供当前选中索引与按钮
- 发出选中变化回调

### 适用场景

- 标签页
- 单选菜单
- 一组选项卡

## 5. `UiMultiSelectButtonGroup`

### 作用

管理一组 `UiSelectableButton` 的多选行为。

### 和 `UiButtonGroup` 的区别

- 不会强制互斥
- 会把按钮激活行为切换为 `Toggle`
- 提供选中索引列表和选中按钮列表

## 6. `UiLabel`

### 作用

显示文本标签。

### 核心能力

- 文本、字体、字体 key
- 文本颜色与背景色
- 自动尺寸
- 横纵对齐
- 内边距
- 自动换行
- 标签主题角色

### 实现细节

- 文字渲染结果会缓存成纹理
- 仅 dirty 时重新生成
- `auto_size` 开启后会根据纹理尺寸自动更新控件大小

### 当前实现注意点

`UiLabel::apply_theme()` 当前只应用颜色与背景相关字段，没有完整使用 `UiStyle::apply_label()` 中的 padding / align 逻辑。

## 7. `UiImageView`

### 作用

显示纹理或纹理子区域。

### 核心能力

- 直接设置纹理
- 通过 key 从资源管理器查找纹理
- 可设置源矩形
- 颜色 tint
- alpha
- 三种缩放模式
  - `Stretch`
  - `Fit`
  - `None`
- 可自动按源尺寸设定控件尺寸

### 适用场景

- 图标
- UI 插图
- 裁切精灵图块

## 8. `UiProgressBar`

### 作用

使用 `UiBar` 作为内部绘制器的进度条控件。

### 职责

- 暴露 `set_progress()`
- 按主题角色应用 `BarStyle`
- 转发绘制给内部 `_bar`

### 特点

逻辑简单，是对 `UiBar` 的轻量封装。

## 9. `UiSlider`

### 作用

可拖动或可用焦点输入调节数值的滑条控件。

### 内部组成

- `UiBar _bar`
- `UiLabel _value_label`

### 核心能力

- 数值范围
- 当前值
- 步长吸附
- 横向 / 纵向
- 滑块尺寸与颜色
- 显示当前值文本
- 精度与后缀
- 焦点左右/上下调值
- 鼠标拖拽调值

### 设计亮点

- 条形显示由 `UiBar` 复用
- 数值文本由内部 `UiLabel` 负责
- 支持鼠标和焦点事件两套交互路径

## 10. `UiScrollBar`

### 作用

作为 `UiScrollPanel` 的可视滚动条。

### 依赖

必须绑定一个 `UiScrollPanel* target`。

### 核心能力

- 横向 / 纵向模式
- 自动跟随目标位置与尺寸
- 控制 thickness、margin、min thumb size
- 支持点击轨道、拖拽 thumb
- 支持 auto hide

### 特点

它并不保存内容尺寸，而是动态向目标面板查询。

## 11. `UiToggle`

### 作用

布尔开关控件。

### 内部组成

- `_label`：左侧标签
- `_value_label`：右侧状态文本

### 核心能力

- On/Off 值
- 左侧标签文本
- On/Off 文本自定义
- 鼠标点击切换
- 焦点确认切换
- 焦点左/右直接设置 false/true

### 视觉行为

- 自绘背景、边框、指示块
- 焦点状态会改变背景色

## 12. `UiTextInput`

### 作用

单行文本输入框。

### 核心能力

- 当前文本与 placeholder
- 字体 / 字体 key
- 最长长度
- 只读模式
- 密码模式
- 光标位置
- 光标闪烁
- 鼠标定位光标
- 键盘输入、删除、Home、End、左右移动

### 关键实现点

- 获得焦点时启动 SDL 文本输入
- 失去焦点时停止 SDL 文本输入
- 渲染文本时使用真实文本或掩码文本
- placeholder 为空时不绘制文字

### 局限

- 当前实现更接近单行输入框
- 没有选择区、复制粘贴、撤销等高级编辑能力

## 13. `UiBar`

### 作用

不是 `GameObject`，而是一个独立的“条形绘制工具类”。

### 主要功能

- 管理 min/max/value
- 支持按 ratio 设置
- 支持四种填充方向
- 绘制背景、填充和边框

### 谁在用

- `UiProgressBar`
- `UiSlider`

## 14. `UiFadeImage`

### 作用

独立图片淡入/淡出特效对象，不属于控件树布局体系。

### 模式

- `FadeIn`
- `FadeOut`
- `FadeInOut`

### 内部机制

- 状态机
- `Timer`
- 通过 alpha 改变纹理透明度
- 完成后自动 `destroy()`

### 特点

它更像一个过场特效对象，而不是标准 UI 控件。

## 15. `ui_mouse_utils.h`

### 作用

提供两个非常关键的输入辅助函数：

- `ui_logical_mouse_position()`
- `ui_mouse_input_allowed(...)`

### 它解决了什么问题

- SDL logical size 模式下鼠标坐标换算
- 切换输入设备时避免鼠标逻辑误触发

很多鼠标型控件都依赖这个头文件。

