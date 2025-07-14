// ledindicator.cpp
#include "ledindicator.h"
#include <QPainter>
#include <QRadialGradient>

LedIndicator::LedIndicator(QWidget *parent) : QWidget(parent),
    m_on(false),
    m_onColor(Qt::green),
    m_offColor(Qt::darkGray),
    m_size(20)
{
    setSize(20);
}

void LedIndicator::setOn(bool on)
{
    if (m_on != on) {
        m_on = on;
        update();
        emit stateChanged(m_on);
    }
}

void LedIndicator::setOnColor(const QColor &color)
{
    if (m_onColor != color) {
        m_onColor = color;
        update();
    }
}

void LedIndicator::setOffColor(const QColor &color)
{
    if (m_offColor != color) {
        m_offColor = color;
        update();
    }
}

void LedIndicator::setSize(int size)
{
    if (size != m_size && size > 0) {
        m_size = size;
        setFixedSize(m_size, m_size);
        update();
    }
}

QSize LedIndicator::sizeHint() const
{
    return QSize(m_size, m_size);
}

QSize LedIndicator::minimumSizeHint() const
{
    return QSize(10, 10);
}

void LedIndicator::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    QRectF rect(1, 1, width() - 2, height() - 2);
    drawLed(painter, rect, m_on ? m_onColor : m_offColor);
}

void LedIndicator::drawLed(QPainter &painter, const QRectF &rect, const QColor &color)
{
    // 绘制LED外框
    QLinearGradient borderGrad(rect.topLeft(), rect.bottomRight());
    borderGrad.setColorAt(0, Qt::lightGray);
    borderGrad.setColorAt(1, Qt::darkGray);
    
    painter.setPen(QPen(borderGrad, 1));
    painter.setBrush(Qt::black);
    painter.drawEllipse(rect);
    
    // 绘制LED发光效果
    QRadialGradient grad(rect.center(), rect.width() / 2);
    QColor centerColor = color.lighter(150);
    QColor edgeColor = color.darker(200);
    
    grad.setColorAt(0, centerColor);
    grad.setColorAt(0.6, color);
    grad.setColorAt(1, edgeColor);
    
    painter.setPen(Qt::NoPen);
    painter.setBrush(grad);
    painter.drawEllipse(rect.adjusted(2, 2, -2, -2));
    
    // 添加高光效果
    if (m_on) {
        QRectF highlight = rect.adjusted(rect.width()/4, rect.height()/4, 
                                       -rect.width()/8, -rect.height()/8);
        QRadialGradient highlightGrad(highlight.topLeft(), highlight.width());
        highlightGrad.setColorAt(0, Qt::white);
        highlightGrad.setColorAt(1, Qt::transparent);
        
        painter.setBrush(highlightGrad);
        painter.drawEllipse(highlight);
    }
}