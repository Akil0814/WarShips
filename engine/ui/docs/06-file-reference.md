# 文件级索引与职责说明

本文件按目录列出当前 `engine/ui` 下每个源码文件的作用、主要依赖与职责。为方便阅读，`.h` 与 `.cpp` 分别列出。

## 1. 根目录

| 文件 | 主要依赖 | 作用与职责 |
| --- | --- | --- |
| `ui_bar.h` | `SDL.h` | 定义通用条形绘制器 `UiBar` 和填充方向枚举；提供数值范围、颜色、边框、padding、渲染接口。 |
| `ui_bar.cpp` | `ui_bar.h`、`<algorithm>` | 实现 `UiBar` 的数值限制、ratio 计算、内容区域计算、填充矩形生成和 SDL 绘制逻辑。 |
| `ui_fade_image.h` | `GameObject`、`Timer` | 定义独立淡入淡出图片对象 `UiFadeImage`，包含播放模式、状态机和计时控制。 |
| `ui_fade_image.cpp` | `ui_fade_image.h` | 实现淡入、停留、淡出状态切换，控制纹理 alpha，结束后自动销毁对象。 |
| `ui_layout.h` | `base/ui_element.h`、`<memory>`、`<vector>` | 定义主线性布局树 `UiLayout`，包括子元素选项、padding、anchor、direction、transform、auto-size 等。 |
| `ui_layout.cpp` | `ui_layout.h`、`<algorithm>` | 实现布局脏标记、内容测量、子节点位置尺寸应用、以及更新/渲染/输入的树状分发。 |
| `ui_mouse_utils.h` | `InputSystem`、`SDL.h` | 提供逻辑坐标鼠标位置换算和“是否允许鼠标输入”的判定工具函数。 |

## 2. `animation/`

| 文件 | 主要依赖 | 作用与职责 |
| --- | --- | --- |
| `animation/ui_transition.h` | `ui_layout.h`、`SDL.h` | 定义 `UiTransition`、过渡状态 `UiTransitionState` 和 easing 枚举。 |
| `animation/ui_transition.cpp` | `ui_transition.h`、`<algorithm>`、`<cmath>` | 实现前进/后退播放、跳转、插值、缓动曲线计算和当前状态刷新。 |

## 3. `base/`

| 文件 | 主要依赖 | 作用与职责 |
| --- | --- | --- |
| `base/ui_element.h` | `GameObject` | UI 元素共同基类；负责主题启用、主题脏标记与 `apply_theme` 抽象接口。 |
| `base/ui_element.cpp` | `ui_element.h`、`style/ui_theme_manager.h` | 实现主题管理器自动注册/注销、reset 时标脏、懒应用主题。 |
| `base/ui_control.h` | `ui_element.h`、`ui_focusable.h` | 把可聚焦接口叠加到 `UiElement` 上，提供 enabled/focused 状态。 |
| `base/ui_control.cpp` | `ui_control.h` | 实现启用/禁用、失焦、返回 `GameObject*` 等默认交互基类逻辑。 |
| `base/ui_focusable.h` | `GameObject`、`InputEvent` | 定义焦点对象接口，供 `UiScreen`、复合控件和交互控件统一管理。 |

## 4. `containers/`

| 文件 | 主要依赖 | 作用与职责 |
| --- | --- | --- |
| `containers/ui_panel.h` | `ui_theme_roles.h`、`ui_layout.h`、`SDL.h` | 定义可见容器 `UiPanel`，增加背景、边框、背景纹理、裁剪和面板主题角色。 |
| `containers/ui_panel.cpp` | `ui_panel.h`、`ResourceManager`、`ui_theme.h`、`ui_style.h` | 实现背景绘制、边框绘制、子内容裁剪、背景纹理解析和主题套用。 |
| `containers/ui_scroll_panel.h` | `ui_panel.h` | 定义带滚动偏移的面板，支持横/纵滚动开关、步长、边界限制和子元素可见性保证。 |
| `containers/ui_scroll_panel.cpp` | `ui_scroll_panel.h`、`ui_mouse_utils.h`、`<algorithm>` | 实现滚轮驱动滚动、最大滚动范围计算、scroll offset 钳制和 ensure-child-visible。 |
| `containers/ui_screen.h` | `ui_transition.h`、`ui_panel.h`、`ui_focusable.h` | 定义屏幕级容器 `UiScreen`，增加开关状态、输入启用、过渡动画和焦点控制。 |
| `containers/ui_screen.cpp` | `ui_screen.h`、`ui_mouse_utils.h`、`<algorithm>` | 实现 open/close、过渡状态应用、鼠标切焦、方向/Tab 导航和焦点集合清理。 |

## 5. `layout/`

| 文件 | 主要依赖 | 作用与职责 |
| --- | --- | --- |
| `layout/ui_grid_layout.h` | `ui_layout.h`、`<memory>`、`<vector>` | 定义独立网格布局器 `UiGridLayout`，支持列数、网格间距、padding 和单元格对齐。 |
| `layout/ui_grid_layout.cpp` | `ui_grid_layout.h`、`<algorithm>` | 实现网格定位、行高计算、子节点生命周期分发和对齐偏移计算。 |

## 6. `style/`

| 文件 | 主要依赖 | 作用与职责 |
| --- | --- | --- |
| `style/ui_theme_roles.h` | 无 | 定义面板、标签、按钮、条形控件的主题角色枚举。 |
| `style/ui_style.h` | `ui_bar.h`、按钮/面板/标签/输入等控件头 | 定义 `ButtonStyle`、`LabelStyle` 等样式结构，以及 `UiStyle` 应用器接口。 |
| `style/ui_style.cpp` | `ui_style.h` | 实现样式结构到控件 setter 的映射逻辑。 |
| `style/ui_theme.h` | `ui_theme_roles.h`、`ui_style.h` | 定义 `UiTheme` 数据结构，把不同语义角色的样式槽位组织成一个主题对象。 |
| `style/ui_theme.cpp` | `ui_theme.h` | 构建当前默认主题 `make_loading_blue_theme()`，提供整套蓝色加载风格。 |
| `style/ui_theme_manager.h` | `ui_theme.h`、`<vector>` | 定义主题单例，负责保存当前主题和所有已注册 UI 元素。 |
| `style/ui_theme_manager.cpp` | `ui_theme_manager.h`、`base/ui_element.h`、`<algorithm>` | 实现主题切换、元素注册/注销和统一标记 dirty。 |

## 7. `widgets/`

| 文件 | 主要依赖 | 作用与职责 |
| --- | --- | --- |
| `widgets/ui_button.h` | `ui_theme_roles.h`、`ui_control.h`、`SDL`、`SDL_mixer` | 定义基础按钮，支持主题/本地颜色/本地纹理三种外观模式，以及音效、点击回调和焦点激活。 |
| `widgets/ui_button.cpp` | `ui_button.h`、`ui_mouse_utils.h`、`ui_theme.h`、`ui_style.h` | 实现按钮渲染、鼠标悬停按压释放、音效播放、回调触发、主题角色套用。 |
| `widgets/ui_button_group.h` | `ui_selectable_button.h`、`<memory>`、`<vector>` | 定义单选按钮组，负责互斥选中与选择变化回调。 |
| `widgets/ui_button_group.cpp` | `ui_button_group.h`、`<algorithm>` | 实现监听器注册清理、按钮互斥同步、当前选中索引维护。 |
| `widgets/ui_image_view.h` | `ui_element.h`、`SDL.h`、`<optional>` | 定义图片显示控件，支持纹理 key、裁切源矩形、tint、alpha、缩放模式与 auto-size。 |
| `widgets/ui_image_view.cpp` | `ui_image_view.h`、`ResourceManager`、`<algorithm>` | 实现纹理解析、目标矩形计算、颜色调制和 SDL 绘制。 |
| `widgets/ui_label.h` | `ui_theme_roles.h`、`ui_element.h`、`texture_loader.h`、`SDL_ttf` | 定义文字标签控件，支持自动尺寸、换行、对齐、padding、字体和主题角色。 |
| `widgets/ui_label.cpp` | `ui_label.h`、`ResourceManager`、`ui_theme.h`、`ui_style.h` | 实现文字纹理缓存、背景绘制、文本布局、字体解析和主题颜色应用。 |
| `widgets/ui_multi_select_button_group.h` | `ui_selectable_button.h`、`<memory>`、`<vector>` | 定义多选按钮组，提供多个按钮的并存选中管理。 |
| `widgets/ui_multi_select_button_group.cpp` | `ui_multi_select_button_group.h`、`<algorithm>` | 实现监听器绑定、按钮状态查询、切换和多选回调分发。 |
| `widgets/ui_progress_bar.h` | `SDL.h`、`ui_bar.h`、`ui_theme_roles.h`、`ui_element.h` | 定义基于 `UiBar` 的进度条控件。 |
| `widgets/ui_progress_bar.cpp` | `ui_progress_bar.h`、`ui_theme.h`、`ui_style.h` | 实现进度设定、内部 `UiBar` 渲染和主题角色应用。 |
| `widgets/ui_scroll_bar.h` | `ui_scroll_panel.h`、`ui_element.h`、`SDL.h` | 定义滚动条控件，支持绑定滚动面板、拖拽 thumb、自动隐藏和自动跟随目标。 |
| `widgets/ui_scroll_bar.cpp` | `ui_scroll_bar.h`、`ui_mouse_utils.h`、`ui_theme.h`、`ui_style.h` | 实现 thumb 计算、轨道/滑块绘制、鼠标拖动同步目标滚动偏移。 |
| `widgets/ui_selectable_button.h` | `ui_text_button.h`、`<functional>`、`<vector>` | 定义可选按钮，在文本按钮上增加 selected 状态和监听器。 |
| `widgets/ui_selectable_button.cpp` | `ui_selectable_button.h`、`<algorithm>`、`<utility>` | 实现选择行为、Toggle/Select 激活模式和选中状态回调。 |
| `widgets/ui_slider.h` | `ui_bar.h`、`ui_control.h`、`ui_label.h` | 定义滑条控件，支持范围、步长、方向、thumb、数值文本与值变化回调。 |
| `widgets/ui_slider.cpp` | `ui_slider.h`、`ui_mouse_utils.h`、`ui_theme.h`、`ui_style.h` | 实现鼠标拖拽调值、焦点方向输入调值、value label 同步和滑块绘制。 |
| `widgets/ui_text_button.h` | `ui_button.h`、`texture_loader.h`、`SDL_ttf` | 定义文字按钮，在按钮基础上增加文本、字体和文本纹理缓存。 |
| `widgets/ui_text_button.cpp` | `ui_text_button.h`、`ResourceManager`、`<algorithm>` | 实现文本纹理生成与更新，并将文字纹理挂到按钮消息纹理。 |
| `widgets/ui_text_input.h` | `ui_control.h`、`texture_loader.h`、`SDL_ttf` | 定义文本输入框，支持 placeholder、长度限制、只读、密码模式、光标与文本变化回调。 |
| `widgets/ui_text_input.cpp` | `ui_text_input.h`、`ResourceManager`、`ui_mouse_utils.h`、`ui_theme.h`、`ui_style.h` | 实现 SDL 文本输入启停、文本编辑、光标定位、闪烁绘制、placeholder 与密码显示。 |
| `widgets/ui_toggle.h` | `ui_control.h`、`ui_label.h` | 定义布尔开关控件，带左侧标签、右侧状态文本和切换回调。 |
| `widgets/ui_toggle.cpp` | `ui_toggle.h`、`ui_mouse_utils.h`、`ui_theme.h`、`ui_style.h` | 实现开关背景/指示块绘制、鼠标切换、焦点事件切换和标签同步。 |

## 8. `composite/`

| 文件 | 主要依赖 | 作用与职责 |
| --- | --- | --- |
| `composite/ui_dialog.h` | `ui_screen.h`、`ui_label.h`、`ui_scroll_bar.h`、`ui_menu_list.h` | 定义对话框组件，封装标题、消息、动作列表、取消动作和动作回调。 |
| `composite/ui_dialog.cpp` | `ui_dialog.h`、`ui_style.h` | 实现对话框 reset、构建内部控件树、显示/隐藏、取消逻辑和动作分发。 |
| `composite/ui_menu_list.h` | `ui_scroll_panel.h`、`ui_focusable.h`、`ui_style.h`、`ui_text_button.h` | 定义滚动菜单列表，支持条目数据、选中索引、按钮样式和焦点导航。 |
| `composite/ui_menu_list.cpp` | `ui_menu_list.h`、`ui_theme.h`、`<algorithm>` | 实现条目重建、滚动步长、选中同步、确认回调和主题驱动的样式重建。 |
| `composite/ui_option_list.h` | `ui_scroll_panel.h`、`ui_style.h`、`ui_focusable.h`、`ui_label.h`、`ui_slider.h`、`ui_toggle.h` | 定义设置列表，支持 Toggle/Slider 两类行控件、样式结构和数值变化回调。 |
| `composite/ui_option_list.cpp` | `ui_option_list.h`、`ui_mouse_utils.h`、`ui_theme.h`、`<algorithm>` | 实现每行的 Panel/Label/Control 组合构建、选中同步、值回写、行视觉刷新和主题重建。 |
| `composite/ui_tab_bar.h` | `ui_panel.h`、`ui_focusable.h`、`ui_style.h`、`ui_button_group.h`、`ui_selectable_button.h` | 定义标签页条，维护 tab 数据、按钮集合、单选组和选中变化回调。 |
| `composite/ui_tab_bar.cpp` | `ui_tab_bar.h`、`<algorithm>` | 实现 tab 按钮重建、左右导航、按钮焦点同步和选中事件派发。 |

## 9. 目录级依赖总结

### 最底层

- `base/`
- `ui_bar.*`
- `ui_mouse_utils.h`

### 建立 UI 树与容器

- `ui_layout.*`
- `layout/ui_grid_layout.*`
- `containers/*`

### 提供外观和主题

- `style/*`

### 构成基础控件

- `widgets/*`

### 构成高层界面

- `composite/*`

### 独立动画辅助

- `animation/ui_transition.*`
- `ui_fade_image.*`

## 10. 学习建议

如果要从文件层面建立最稳的理解，推荐顺序如下：

1. `base/ui_element.*`
2. `base/ui_control.*`
3. `ui_layout.*`
4. `containers/ui_panel.*`
5. `containers/ui_scroll_panel.*`
6. `containers/ui_screen.*`
7. `style/ui_theme.*`
8. `style/ui_style.*`
9. `widgets/ui_button.*`
10. `widgets/ui_label.*`
11. `widgets/ui_slider.*`
12. `widgets/ui_text_input.*`
13. `composite/ui_menu_list.*`
14. `composite/ui_option_list.*`
15. `composite/ui_dialog.*`

