#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // 设置窗口大小
    setFixedSize(1000, 700);
    
    // 创建中央部件和主布局
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(50, 50, 50, 50);
    
    // 创建堆叠窗口用于多个界面
    stackedWidget = new QStackedWidget(this);
    mainLayout->addWidget(stackedWidget);
    
    // 创建主界面
    createMainInterface();
    
    // 创建其他界面
    createOtherInterfaces();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    
    // 绘制背景图片
    QPixmap background(":/bg.png"); // 使用资源文件中的背景图
    if(!background.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background);
    } else {
        // 如果没有背景图，绘制默认的科技感渐变背景
        QLinearGradient gradient(0, 0, width(), height());
        gradient.setColorAt(0, QColor(10, 20, 40));
        gradient.setColorAt(1, QColor(5, 10, 25));
        // gradient.setColorAt(0, QColor(144, 238, 144));  // 浅绿色
        // gradient.setColorAt(1, QColor(173, 216, 230));  // 浅蓝色
        painter.fillRect(rect(), gradient);
    }
    
    // 添加一些科技感元素
    painter.setPen(QPen(QColor(0, 150, 255, 50), 1));
    for (int i = 0; i < width(); i += 20) {
        painter.drawLine(i, 0, i, height());
    }
    for (int i = 0; i < height(); i += 20) {
        painter.drawLine(0, i, width(), i);
    }
}

void MainWindow::createMainInterface() {
    QWidget *mainPage = new QWidget();
    QHBoxLayout *buttonLayout = new QHBoxLayout(mainPage);
    buttonLayout->setContentsMargins(0, 200, 0, 0);
    buttonLayout->setSpacing(50);
    
    // 创建三个科技感按钮
    QStringList buttonNames = {"控制中心", "数据分析", "系统设置"};
    for (int i = 0; i < 3; ++i) {
        TechButton *button = new TechButton(buttonNames[i], this);
        button->setFixedSize(200, 60);
        connect(button, &QPushButton::clicked, this, [this, i]() {
            stackedWidget->setCurrentIndex(i + 1); // 切换到对应界面
        });
        buttonLayout->addWidget(button);
    }
    
    stackedWidget->addWidget(mainPage);
}

void MainWindow::createOtherInterfaces() {
    // 创建控制中心界面
    QWidget *controlPage = createPage("控制中心", "系统监控中...", QColor(30, 70, 120));
    
    // 创建数据分析界面
    QWidget *dataPage = createPage("数据分析", "处理数据中...", QColor(40, 100, 100));
    
    // 创建系统设置界面
    QWidget *settingsPage = createPage("系统设置", "配置系统参数...", QColor(70, 60, 120));
    
    // 为每个界面添加返回按钮
    addBackButton(controlPage);
    addBackButton(dataPage);
    addBackButton(settingsPage);
    
    // 添加到堆叠窗口
    stackedWidget->addWidget(controlPage);
    stackedWidget->addWidget(dataPage);
    stackedWidget->addWidget(settingsPage);
}

QWidget* MainWindow::createPage(const QString &title, const QString &content, const QColor &color) {
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);
    
    // 标题
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(QString(
        "QLabel {"
        "   color: %1;"
        "   font-size: 32px;"
        "   font-weight: bold;"
        "   padding: 20px;"
        "}"
    ).arg(color.lighter(150).name()));
    
    // 内容
    QLabel *contentLabel = new QLabel(content);
    contentLabel->setAlignment(Qt::AlignCenter);
    contentLabel->setStyleSheet(
        "QLabel {"
        "   color: #CCCCCC;"
        "   font-size: 24px;"
        "   padding: 50px;"
        "}"
    );
    
    layout->addWidget(titleLabel);
    layout->addWidget(contentLabel);
    layout->addStretch();
    
    return page;
}

void MainWindow::addBackButton(QWidget *page) {
    QHBoxLayout *backLayout = new QHBoxLayout();
    TechButton *backButton = new TechButton("返回主界面", this);
    backButton->setFixedSize(150, 40);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(0); // 返回主界面
    });
    
    backLayout->addStretch();
    backLayout->addWidget(backButton);
    backLayout->addStretch();
    
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(page->layout());
    if (mainLayout) {
        mainLayout->addLayout(backLayout);
    }
}
