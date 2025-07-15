#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include "battery.h"
#include "dashboard.h"
#include "compasswidget.h"
#include "ringprogresswidget.h"
#include "switchbutton.h"
#include "ledindicator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Battery *battery;
    int batteryValue = 0;

    DashBoard *dashboard;
    int dashboardValue = 0;

    CompassWidget *compass;
    QSlider *angleSlider;

    RingProgressWidget *ringProgress;
    int ringProgressValue = 0;

    SwitchButton *switchButton;
    QLabel *switchStatusLabel;

    LedIndicator *ledIndicator;
    QPushButton *toggleLedButton;

signals:
    void batteryChanged(int newValue);

private slots:
    void updateBattery();

    void updateDashBoard();

    void updateRingProgress();
};
#endif // MAINWINDOW_H
