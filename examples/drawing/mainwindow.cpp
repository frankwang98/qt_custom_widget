#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // DrawingManager::instance()->addShape("Circle", "Solid");
    // DrawingManager::instance()->addShape("Rectangle", "Gradient");
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    qDebug() << "Paint Event";
    QPainter painter(this);
    DrawingManager::instance()->drawShapes(painter);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Mouse Pressed";
        int x = event->x();
        int y = event->y();
        // DrawingManager::instance()->addShapeAtPosition("Circle", "Solid", x, y);
        DrawingManager::instance()->addShapeAtPosition("Rectangle", "Gradient", x, y);
        update();
    }
}
