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

    battery = new Battery(this);
    battery->setGeometry(50, 100, 150, 80);
    battery->setValue(batteryValue);

    dashboard = new DashBoard(this);
    dashboard->setGeometry(200, 50, 250, 250);
    dashboard->setValue(0);

    compass = new CompassWidget(this);
    compass->setGeometry(500, 50, 250, 250);
    angleSlider = new QSlider(Qt::Horizontal, this);
    angleSlider->setRange(0, 359);
    angleSlider->setValue(0);
    angleSlider->setGeometry(500, 300, 250, 30);
    connect(angleSlider, &QSlider::valueChanged, compass, &CompassWidget::setAngle);

    ringProgress = new RingProgressWidget(this);
    ringProgress->setGeometry(50, 300, 250, 250);
    ringProgress->setValue(0);

    switchButton = new SwitchButton(this);
    switchButton->setChecked(true);
    switchButton->setGeometry(500, 400, 120, 30);
    switchStatusLabel = new QLabel("状态: 开", this);
    switchStatusLabel->setGeometry(500, 450, 120, 50);
    connect(switchButton, &SwitchButton::toggled, [this](bool checked) {
        switchStatusLabel->setText(checked ? "状态: 开" : "状态: 关");
    });

    ledIndicator = new LedIndicator(this);
    ledIndicator->setOn(true);
    ledIndicator->setOnColor(QColor(255, 0, 0));
    ledIndicator->setSize(50);
    ledIndicator->setGeometry(350, 380, 30, 30);
    toggleLedButton = new QPushButton("切换LED状态", this);
    toggleLedButton->setGeometry(350, 450, 120, 50);
    connect(toggleLedButton, &QPushButton::clicked, [this]() {
        ledIndicator->setOn(!ledIndicator->isOn());
    });
    connect(switchButton, &SwitchButton::toggled, [this](bool checked) {
        ledIndicator->setOn(checked);
    }); // connect switchButton to ledIndicator

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateBattery);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDashBoard);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateRingProgress);
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
