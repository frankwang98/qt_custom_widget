#include "techbutton.h"

TechButton::TechButton(const QString &text, QWidget *parent) 
    : QPushButton(text, parent), m_glowColor(0, 150, 255), glowAnimation(nullptr) {
    setStyleSheet(
        "QPushButton {"
        "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "       stop: 0 #2060A0, stop: 0.5 #104080, stop: 1 #082040);"
        "   color: white;"
        "   border: 1px solid #4080FF;"
        "   border-radius: 5px;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   padding: 10px;"
        "}"
        "QPushButton:hover {"
        "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "       stop: 0 #3090D0, stop: 0.5 #2060B0, stop: 1 #104070);"
        "}"
        "QPushButton:pressed {"
        "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "       stop: 0 #104080, stop: 0.5 #082040, stop: 1 #041020);"
        "}"
    );
    
    // 添加发光效果
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(15);
    effect->setColor(m_glowColor);
    effect->setOffset(0, 0);
    setGraphicsEffect(effect);
    
    // 创建发光动画
    glowAnimation = new QPropertyAnimation(this, "glowColor");
    glowAnimation->setEasingCurve(QEasingCurve::InOutSine);
    glowAnimation->setDuration(1500);
    glowAnimation->setStartValue(QColor(0, 150, 255, 100));
    glowAnimation->setEndValue(QColor(0, 200, 255, 200));
    glowAnimation->setLoopCount(-1); // 无限循环
    glowAnimation->start();
}

QColor TechButton::getGlowColor() const {
    return m_glowColor;
}

void TechButton::setGlowColor(const QColor &color) {
    m_glowColor = color;
    QGraphicsDropShadowEffect *effect = qobject_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
    if (effect) {
        effect->setColor(color);
    }
    update();
}

void TechButton::enterEvent(QEvent *event) {
    QPushButton::enterEvent(event);
    if (glowAnimation) {
        glowAnimation->setDuration(500);
    }
}

void TechButton::leaveEvent(QEvent *event) {
    QPushButton::leaveEvent(event);
    if (glowAnimation) {
        glowAnimation->setDuration(1500);
    }
}