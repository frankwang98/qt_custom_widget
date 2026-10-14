# Qt Custom Widgets · 轻量级 Qt Widgets 控件合集

独立、可复用的 C++/Qt Widgets 控件，保留原有 qmake 工程，新增 CMake 静态库和交互展示程序。适用于桌面仪表盘、状态监控与工具软件。

![控件展示](assets/demo2.png)

## 控件

| 控件 | 用途 | 主要 API |
| --- | --- | --- |
| Battery | 电量和报警状态 | `setValue`, `setRange`, `setAlarmValue` |
| DashBoard | 通用仪表盘 | `setValue`, `setMinValue`, `setMaxValue`, `setUnit` |
| CompassWidget | 方位角 | `setAngle` |
| RingProgressWidget | 圆环进度 | `setRange`, `setValue` |
| SwitchButton | 带动画的开关 | `setChecked`, `toggled` |
| LedIndicator | LED 状态灯 | `setOn`, `setOnColor` |
| Speedometer | 数值/速度表盘 | `setIndicatorValue`, `setUnitText` |

> 不同控件历史 API 命名有所差异；本次保留已有 API，避免破坏旧项目。

## 构建（推荐 CMake）

要求 CMake >= 3.16、C++17、Qt 5 或 Qt 6（Widgets）。

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/qt_widget_gallery
```

在 Windows 上使用对应构建配置下的可执行文件。仅使用控件库可设置 `-DBUILD_WIDGET_DEMO=OFF`。

其他 CMake 项目可以用 `add_subdirectory(path/to/qt_custom_widget)`，然后 `target_link_libraries(your_app PRIVATE qt_custom_widgets)`。

仍支持在 Qt Creator 中打开 `qt_custom_control.pro`，或使用 qmake + make。

## 交互与布局

主 Demo 使用滚动网格布局，支持调整窗口尺寸；电量、仪表盘和进度自动演示，指南针与速度表盘可拖动滑块，LED 可通过按钮或开关切换。顶部可切换浅色、深色、AMOLED、Material 与系统主题。开关支持鼠标和 Space/Enter 键，并显示键盘焦点。绘制使用 Qt 的逻辑坐标，建议在目标系统上检查高 DPI 缩放、窗口缩放与不同字体。

## 其他独立示例

- [绘图与设计模式](examples/drawing/README.md)：`examples/drawing/draw.pro`
- [停车场动画](examples/parking/README.md)：`examples/parking/park.pro`
- `bg/bg.pro`：按钮示例

这些示例保留独立工程，不包含在主控件库中。

## 验证

GitHub Actions 对 Qt5/Qt6 执行 CMake 构建。CI 不等同于人工 GUI 视觉验收；请在本机运行 Gallery 验证外观与交互。

## License

MIT，详见 [LICENSE](LICENSE)。
