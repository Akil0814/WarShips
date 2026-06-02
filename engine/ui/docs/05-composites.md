# 复合控件与完整界面

复合控件的核心思想是：不从零重写所有逻辑，而是组合已有容器与基础控件形成更高层的 UI 单元。

## 1. `UiMenuList`

### 它是什么

一个带滚动能力、支持单项选中和确认的菜单列表。

### 继承关系

- `UiScrollPanel`
- `UiFocusable`

### 内部结构

- `_items`：菜单数据
- `_buttons`：每个条目对应一个 `UiTextButton`
- `_selected_index`

### 工作方式

1. `set_items()` / `add_item()` 触发 `rebuild_items()`
2. 为每个条目构建一个 `UiTextButton`
3. 把按钮加入自身布局树
4. 当前选中项通过 `set_focused()` 反映成按钮焦点高亮
5. 焦点事件支持上下切换和确认触发

### 学习重点

这是理解“如何在当前 UI 系统里做列表”的最好例子。

## 2. `UiOptionList`

### 它是什么

一个带滚动能力、每一行包含“标签 + 控件”的设置列表。

### 每行可承载的控件类型

- `Toggle`
- `Slider`

### 行结构

一行由 `RowWidgets` 组成：

- `_panel`
- `_label`
- `_control_object`
- `_control`

### 工作方式

1. `set_items()` 或风格改变触发 `rebuild_rows()`
2. 每个数据项生成一个行面板
3. 行面板内放左侧 `UiLabel`
4. 再按类型创建 `UiToggle` 或 `UiSlider`
5. 控件值变化时回写 `_items`
6. 通过 `_selected_index` 控制当前行焦点与高亮

### 这个类很有代表性

因为它完整展示了：

- 组合式 UI
- 数据模型与控件树同步
- 焦点与行视觉同步
- 主题影响复合控件内部样式

### 当前实现特点

- 很多变化会整体重建所有行
- `handle_row_click()` 目前没有接入调用链
- 主题变更会重建行树

## 3. `UiTabBar`

### 它是什么

一个水平标签页条。

### 内部组成

- `UiPanel` 容器能力
- `UiButtonGroup` 单选同步器
- 多个 `UiSelectableButton`

### 工作方式

1. `set_tabs()` / `add_tab()` 触发 `rebuild_tabs()`
2. 每个 tab 变成一个 `UiSelectableButton`
3. `UiButtonGroup` 统一管理选中状态
4. `handle_focused_input_event()` 用左右切换选项
5. `Confirm` 时发出当前选中项回调

### 值得注意的设计

- `UiTabBar` 自己实现 `UiFocusable`
- 但内部按钮也有自己的按钮语义
- 这里的焦点重点是“条级别导航”，不是每个按钮独立进屏幕焦点队列

## 4. `UiDialog`

### 它是什么

一个基于 `UiScreen` 的完整对话框界面。

### 主要组成

- 标题 `UiLabel`
- 消息 `UiLabel`
- 动作列表 `UiMenuList`
- 预留的动作滚动条 `UiScrollBar`

### 工作方式

1. 构造时 `ensure_controls()`
2. `reset()` 配置尺寸、对齐、过渡和内部控件
3. `rebuild()` 清空子树并重新挂载标题、消息、动作列表
4. `show_dialog()` 调用 `open()`
5. `hide_dialog()` 调用 `close()`
6. `Cancel` 输入优先尝试执行取消动作

### 它体现了什么

- `UiScreen` 如何作为“整页 UI 容器”使用
- `UiMenuList` 如何作为动作选择区复用
- 对话框逻辑层如何和 UI 表现层解耦

### 当前实现中的真实行为

- 动作触发时只调用 `_on_action`
- `handle_action()` 当前不会自动关闭对话框
- `_action_scroll_bar` 已创建并绑定目标，但 `rebuild()` 没有把它加入子树，因此当前看不到滚动条

## 5. `UiScreen` 与复合控件的关系

在这一层里，最值得掌握的是：

- `UiScreen` 管总生命周期
- `UiMenuList` / `UiOptionList` / `UiTabBar` 管局部交互模型
- 复合控件大都把复杂逻辑封装在自身内部，而不是把所有逻辑堆到某个大屏类里

## 6. 当前系统如何组织一个完整 UI 页面

一个完整页面通常可以这样构建：

1. 顶层使用 `UiScreen`
2. 页面分区使用 `UiPanel` 或 `UiScrollPanel`
3. 文本信息使用 `UiLabel`
4. 主要操作使用 `UiButton` / `UiTextButton`
5. 列表选择使用 `UiMenuList`
6. 设置项使用 `UiOptionList`
7. 标签切换使用 `UiTabBar`
8. 模态弹窗使用 `UiDialog`

## 7. 复合控件层的设计风格总结

- 优先复用已有基础控件
- 通过 rebuild 维护内部对象树
- 通过外部回调把交互结果暴露出去
- 焦点既可以交给 `UiScreen`，也可以在组件内部再细分
- 样式覆盖与主题默认值并存

