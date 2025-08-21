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
#include <QGraphicsDropShadowEffect>
#include <QEvent>

class TechButton : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(QColor glowColor READ getGlowColor WRITE setGlowColor)
public:
    TechButton(const QString &text, QWidget *parent = nullptr);
    QColor getGlowColor() const;
    void setGlowColor(const QColor &color);
    
protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    
private:
    QColor m_glowColor;
    QPropertyAnimation *glowAnimation;
};