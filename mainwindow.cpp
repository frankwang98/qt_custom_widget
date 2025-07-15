#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(":/style/lightblue.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&file);
        QString styleSheet = ts.readAll();
        this->setStyleSheet(styleSheet);
        file.close();
    }
    this->setWindowIcon(QIcon(":/style/icon.png"));

    // battery
    battery = new Battery(this);
    battery->setGeometry(50, 100, 150, 80);
    battery->setValue(batteryValue);

    // dashboard
    dashboard = new DashBoard(this);
    dashboard->setGeometry(200, 50, 250, 250);
    dashboard->setValue(0);

    // compass
    compass = new CompassWidget(this);
    compass->setGeometry(500, 50, 250, 250);
    angleSlider = new QSlider(Qt::Horizontal, this);
    angleSlider->setRange(0, 359);
    angleSlider->setValue(0);
    angleSlider->setGeometry(500, 300, 250, 30);
    connect(angleSlider, &QSlider::valueChanged, compass, &CompassWidget::setAngle);

    // ring progress
    ringProgress = new RingProgressWidget(this);
    ringProgress->setGeometry(200, 310, 230, 230);
    ringProgress->setValue(0);

    // switch button
    switchButton = new SwitchButton(this);
    switchButton->setChecked(true);
    switchButton->setGeometry(50, 300, 120, 30);
    switchStatusLabel = new QLabel("状态: 开", this);
    switchStatusLabel->setGeometry(50, 350, 120, 50);
    connect(switchButton, &SwitchButton::toggled, [this](bool checked) {
        switchStatusLabel->setText(checked ? "状态: 开" : "状态: 关");
    });

    // led indicator
    ledIndicator = new LedIndicator(this);
    ledIndicator->setOn(true);
    ledIndicator->setOnColor(QColor(255, 0, 0));
    ledIndicator->setSize(50);
    ledIndicator->setGeometry(50, 400, 30, 30);
    toggleLedButton = new QPushButton("切换LED状态", this);
    toggleLedButton->setGeometry(50, 480, 120, 50);
    connect(toggleLedButton, &QPushButton::clicked, [this]() {
        ledIndicator->setOn(!ledIndicator->isOn());
    });
    connect(switchButton, &SwitchButton::toggled, [this](bool checked) {
        ledIndicator->setOn(checked);
    }); // connect switchButton to ledIndicator

    // speedometer
    speedometer = new Speedometer(this);
    speedometer->setIndicatorValue(0);
    speedometer->setGeometry(500, 330, 230, 230);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateBattery);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDashBoard);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateRingProgress);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSpeedometer);
    timer->start(100);
    connect(this, SIGNAL(batteryChanged(int)), battery, SLOT(setValue(int))); // with parameter    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateBattery() 
{
    // 更新电量值，这里假设电量值从0到100循环
    batteryValue = (batteryValue + 1) % 101;
    emit batteryChanged(batteryValue); // signal slot()
    // battery->setValue(batteryValue); // direct set
}

void MainWindow::updateDashBoard()
{
    // 更新仪表盘值，这里假设仪表盘值从0到100循环
    dashboardValue = (dashboardValue + 1) % 101;
    dashboard->setValue(dashboardValue);
}

void MainWindow::updateRingProgress()
{
    // 更新环形进度条值，这里假设环形进度条值从0到100循环
    ringProgressValue = (ringProgressValue + 1) % 101;
    ringProgress->setValue(ringProgressValue);
}

void MainWindow::updateSpeedometer()
{
    // 更新速度表值
    speedometerValue = (speedometerValue + 10) % 1001;
    speedometer->setIndicatorValue(speedometerValue);
}
