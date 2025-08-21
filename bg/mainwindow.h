#include "techbutton.h"
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>
#include <QFont>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QGraphicsEffect>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    
protected:
    void paintEvent(QPaintEvent *event) override;
    
private:
    void createMainInterface();
    void createOtherInterfaces();
    QWidget* createPage(const QString &title, const QString &content, const QColor &color);
    void addBackButton(QWidget *page);
    
    QStackedWidget *stackedWidget;
};