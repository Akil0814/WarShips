# UI 系统学习文档

这组文档用于帮助理解 `G:\Coding\Projects\WarShips\engine\ui` 当前目录下 UI 系统的架构、运行流程、模块分层与文件职责。内容基于当前源码实现整理，重点是“现在这份代码实际上怎么工作”。

## 建议阅读顺序

1. [01-system-overview.md](./01-system-overview.md)
2. [02-runtime-flow.md](./02-runtime-flow.md)
3. [03-core-layout-theme.md](./03-core-layout-theme.md)
4. [04-widgets.md](./04-widgets.md)
5. [05-composites.md](./05-composites.md)
6. [06-file-reference.md](./06-file-reference.md)

## 文档内容概览

- `01-system-overview.md`
  - UI 系统整体分层
  - 和引擎其他模块的连接点
  - 主要对象关系图
- `02-runtime-flow.md`
  - 创建、主题应用、布局、渲染、输入、焦点、滚动、过渡动画的真实流程
- `03-core-layout-theme.md`
  - 基类、布局系统、容器系统、主题系统、动画系统的职责拆解
- `04-widgets.md`
  - 所有基础控件的行为、状态、依赖和适用场景
- `05-composites.md`
  - 高层组合控件和完整 UI 界面的组织方式
- `06-file-reference.md`
  - 当前目录下每个 `.h/.cpp` 文件的作用、主要依赖、职责摘要

## 当前 UI 系统的核心认识

- 它建立在 `GameObject` 之上，因此天然继承了引擎已有的更新、渲染、输入、可见性、激活状态和时间缩放机制。
- 它不是“立即模式 UI”，而是一个层级化的对象树系统。
- 主题应用是懒更新的：元素只在需要时刷新主题，而不是统一全量重刷。
- 布局与外观分离得比较清楚：
  - `UiLayout` / `UiGridLayout` 决定排布
  - `UiPanel` / `UiLabel` / `UiButton` 等决定绘制
  - `UiTheme` / `UiStyle` 决定主题风格
- 输入分成两条路径：
  - 鼠标输入由各控件在 `on_input` 中轮询
  - 键盘/手柄导航由 `UiFocusable::handle_focused_input_event` 处理
- 复杂组件大多采用“内部组合已有控件”的方式实现，而不是在单个类中手写所有逻辑。

## 阅读源码时可以重点关注的设计点

- `UiElement` 如何把主题系统挂到所有 UI 对象上
- `UiLayout` 如何维护 `_children` 并负责树状分发
- `UiScreen` 如何在 `UiPanel` 之上叠加开关、过渡和焦点管理
- `UiOptionList`、`UiMenuList`、`UiTabBar` 如何通过组合基础控件构建更高层 UI
- 主题系统中“主题数据”和“应用主题的方法”是如何解耦的

