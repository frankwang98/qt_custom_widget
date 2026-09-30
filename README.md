# Qt 控件与示例库

集中维护个人 Qt Widgets 控件和小型交互示例。每个示例保留独立工程，可单独打开和构建。

## 控件展示

仓库根目录的 `qt_custom_control.pro` 是原有控件展示工程，包含电量控件（引用）、LED 指示灯、切换按钮、仪表盘、指南针、圆环进度条和速度表盘。另有 `bg/bg.pro` 按钮示例。

![控件展示](assets/demo2.png)

## 独立示例

| 示例 | 内容 | 工程入口 |
| --- | --- | --- |
| [绘图与设计模式](examples/drawing/README.md) | 形状工厂、填充策略、绘图管理和 Qt 绘制 | `examples/drawing/draw.pro` |
| [停车场动画](examples/parking/README.md) | 多车绘制、轨迹、简易泊车和碰撞提示 | `examples/parking/park.pro` |

这两个示例分别从 [qt_drawing](https://github.com/frankwang98/qt_drawing) 与 [qt_parkinglot](https://github.com/frankwang98/qt_parkinglot) 整理进入本仓库，保留原有实现与工程文件。各自仍为独立应用，不与控件展示工程一起编译。

## 构建

安装带 Qt Widgets 的 Qt 开发环境，在 Qt Creator 中打开对应的 `.pro`，选择已安装的 Kit 后构建运行。命令行也可以在对应目录执行 `qmake` 与 `make`（Windows 使用相应 Kit 的构建工具）。

本仓库使用原有 qmake 工程；尚未在当前环境编译验证。迁移只整合目录和说明，后续功能调整在这里维护。

## 许可证

MIT，见 [LICENSE](LICENSE)。
