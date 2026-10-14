#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QFile>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QScrollArea>
#include <QSlider>
#include <QSpinBox>
#include <QTextStream>
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle(tr("Qt Custom Widgets · Gallery"));
    setWindowIcon(QIcon(":/style/icon.png"));
    resize(1040, 760);
    setMinimumSize(480, 400);

    auto *vertical = new QVBoxLayout();
    vertical->setContentsMargins(18, 16, 18, 16);
    vertical->setSpacing(14);

    auto *toolbar = new QHBoxLayout();
    auto *heading = new QLabel(tr("Widget Gallery"), this);
    QFont headingFont = heading->font();
    headingFont.setPointSize(17);
    headingFont.setBold(true);
    heading->setFont(headingFont);
    toolbar->addWidget(heading);
    toolbar->addStretch();
    toolbar->addWidget(new QLabel(tr("Theme:"), this));
    auto *theme = new QComboBox(root);
    theme->addItem(tr("Light blue"), "lightblue");
    theme->addItem(tr("Elegant dark"), "elegantdark");
    theme->addItem(tr("AMOLED"), "amoled");
    theme->addItem(tr("Material"), "material");
    theme->addItem(tr("System"), "");
    toolbar->addWidget(theme);
    vertical->addLayout(toolbar);

    auto *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    auto *content = new QWidget(scroll);
    auto *grid = new QGridLayout(content);
    grid->setSpacing(14);

    auto card = [content, grid](const QString &title, QWidget *widget, int row, int col) {
        auto *group = new QGroupBox(title, content);
        auto *layout = new QVBoxLayout(group);
        layout->setSpacing(10);
        widget->setParent(group);
        widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(widget, 1);
        group->setMinimumHeight(245);
        grid->addWidget(group, row, col);
        return layout;
    };

    battery = new Battery();
    battery->setValue(batteryValue);
    card(tr("Battery"), battery, 0, 0);

    dashboard = new DashBoard();
    dashboard->setValue(0);
    card(tr("Dashboard"), dashboard, 0, 1);

    compass = new CompassWidget();
    auto *compassLayout = card(tr("Compass"), compass, 1, 0);
    angleSlider = new QSlider(Qt::Horizontal);
    angleSlider->setRange(0, 359);
    auto *angleLabel = new QLabel(tr("Heading: 0°"));
    compassLayout->addWidget(angleLabel);
    compassLayout->addWidget(angleSlider);
    connect(angleSlider, &QSlider::valueChanged, compass, &CompassWidget::setAngle);
    connect(angleSlider, &QSlider::valueChanged, angleLabel, [angleLabel](int value) {
        angleLabel->setText(QObject::tr("Heading: %1°").arg(value));
    });

    ringProgress = new RingProgressWidget();
    ringProgress->setValue(0);
    card(tr("Ring progress"), ringProgress, 1, 1);

    auto *controls = new QWidget();
    auto *controlsLayout = card(tr("Switch and LED"), controls, 2, 0);
    auto *controlRow = new QHBoxLayout(controls);
    switchButton = new SwitchButton(controls);
    switchButton->setChecked(true);
    switchButton->setAccessibleName(tr("LED switch"));
    controlRow->addWidget(switchButton);
    switchStatusLabel = new QLabel(tr("On"), controls);
    controlRow->addWidget(switchStatusLabel);
    ledIndicator = new LedIndicator(controls);
    ledIndicator->setOn(true);
    ledIndicator->setOnColor(QColor(255, 0, 0));
    ledIndicator->setSize(32);
    controlRow->addWidget(ledIndicator);
    controlRow->addStretch();
    controlsLayout->addWidget(new QLabel(tr("Click or use Space / Enter to toggle.")));
    toggleLedButton = new QPushButton(tr("Toggle LED"));
    controlsLayout->addWidget(toggleLedButton);
    connect(switchButton, &SwitchButton::toggled, this, [this](bool checked) {
        switchStatusLabel->setText(checked ? tr("On") : tr("Off"));
        ledIndicator->setOn(checked);
    });
    connect(toggleLedButton, &QPushButton::clicked, this, [this]() {
        switchButton->setChecked(!switchButton->isChecked());
    });

    speedometer = new Speedometer();
    speedometer->setIndicatorValue(0);
    auto *speedLayout = card(tr("Speedometer"), speedometer, 2, 1);
    auto *speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setRange(0, 1024);
    speedSlider->setValue(0);
    speedLayout->addWidget(speedSlider);
    connect(speedSlider, &QSlider::valueChanged, speedometer, [this](int value) {
        speedometer->setIndicatorValue(value);
    });
    auto *unitRow = new QHBoxLayout();
    unitRow->addWidget(new QLabel(tr("Unit:")));
    auto *unit = new QComboBox();
    unit->addItems({"KB/S", "km/h", "rpm"});
    unitRow->addWidget(unit);
    speedLayout->addLayout(unitRow);
    connect(unit, &QComboBox::currentTextChanged, speedometer, &Speedometer::setUnitText);

    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(1, 1);
    scroll->setWidget(content);
    vertical->addWidget(scroll, 1);
    ui->centralwidget->setLayout(vertical);

    connect(theme, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this, theme](int) {
        const QString name = theme->currentData().toString();
        if (name.isEmpty()) { setStyleSheet(QString()); return; }
        QFile file(QString(":/style/%1.qss").arg(name));
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            setStyleSheet(QString::fromUtf8(file.readAll()));
    });
    theme->setCurrentIndex(1);
    theme->setCurrentIndex(0);

    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateBattery);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDashBoard);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateRingProgress);
    timer->start(120);
}
MainWindow::~MainWindow() { delete ui; }
void MainWindow::updateBattery() {
    batteryValue = (batteryValue + 1) % 101;
    emit batteryChanged(batteryValue);
    battery->setValue(batteryValue);
}
void MainWindow::updateDashBoard() {
    dashboardValue = (dashboardValue + 1) % 101;
    dashboard->setValue(dashboardValue);
}
void MainWindow::updateRingProgress() {
    ringProgressValue = (ringProgressValue + 1) % 101;
    ringProgress->setValue(ringProgressValue);
}
void MainWindow::updateSpeedometer() {
    speedometerValue = (speedometerValue + 10) % 1001;
    speedometer->setIndicatorValue(speedometerValue);
}
