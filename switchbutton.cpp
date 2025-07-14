// switchbutton.cpp
#include "switchbutton.h"
#include <QPainter>
#include <QEasingCurve>

SwitchButton::SwitchButton(QWidget *parent) : QWidget(parent),
    m_checked(false),
    m_checkedColor(QColor(100, 184, 255)),
    m_uncheckedColor(QColor(200, 200, 200)),
    m_thumbColor(Qt::white),
    m_thumbPosition(0)
{
    setMinimumSize(50, 30);
    
    m_animation = new QPropertyAnimation(this, "thumbPosition");
    m_animation->setDuration(200);
    m_animation->setEasingCurve(QEasingCurve::InOutQuad);
    
    connect(m_animation, &QPropertyAnimation::valueChanged, [this]() { update(); });
}

void SwitchButton::setChecked(bool checked)
{
    if (m_checked != checked) {
        m_checked = checked;
        updateThumbPosition();
        emit toggled(m_checked);
    }
}

void SwitchButton::setCheckedColor(const QColor &color)
{
    if (m_checkedColor != color) {
        m_checkedColor = color;
        update();
    }
}

void SwitchButton::setUncheckedColor(const QColor &color)
{
    if (m_uncheckedColor != color) {
        m_uncheckedColor = color;
        update();
    }
}

void SwitchButton::setThumbColor(const QColor &color)
{
    if (m_thumbColor != color) {
        m_thumbColor = color;
        update();
    }
}

QSize SwitchButton::sizeHint() const
{
    return QSize(60, 30);
}

void SwitchButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 绘制背景
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_checked ? m_checkedColor : m_uncheckedColor);
    
    int radius = height() / 2;
    painter.drawRoundedRect(rect(), radius, radius);
    
    // 绘制滑块
    painter.setBrush(m_thumbColor);
    int thumbRadius = height() - 6;
    int thumbX = m_thumbPosition * (width() - thumbRadius - 4) + thumbRadius / 2 + 2;
    painter.drawEllipse(QPointF(thumbX, height() / 2.0), thumbRadius / 2, thumbRadius / 2);
}

void SwitchButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setChecked(!m_checked);
    }
}

void SwitchButton::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    updateThumbPosition();
}

void SwitchButton::updateThumbPosition()
{
    qreal target = m_checked ? 1.0 : 0.0;
    if (m_animation->state() == QPropertyAnimation::Running) {
        m_animation->stop();
    }
    m_animation->setStartValue(m_thumbPosition);
    m_animation->setEndValue(target);
    m_animation->start();
}