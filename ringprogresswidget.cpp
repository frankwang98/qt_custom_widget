// ringprogresswidget.cpp
#include "ringprogresswidget.h"
#include <QPainter>
#include <QPainterPath>

RingProgressWidget::RingProgressWidget(QWidget *parent) : QWidget(parent),
    m_value(0),
    m_minimum(0),
    m_maximum(100),
    m_ringColor(Qt::blue),
    m_backgroundColor(Qt::transparent), // gray
    m_textColor(Qt::black),
    m_ringWidth(20)
{
    setMinimumSize(50, 50);
}

void RingProgressWidget::setValue(int value)
{
    if (value != m_value && value >= m_minimum && value <= m_maximum) {
        m_value = value;
        update();
        emit valueChanged(m_value);
    }
}

void RingProgressWidget::setMinimum(int min)
{
    if (min != m_minimum) {
        m_minimum = min;
        if (m_value < m_minimum)
            setValue(m_minimum);
        update();
    }
}

void RingProgressWidget::setMaximum(int max)
{
    if (max != m_maximum) {
        m_maximum = max;
        if (m_value > m_maximum)
            setValue(m_maximum);
        update();
    }
}

void RingProgressWidget::setRange(int min, int max)
{
    setMinimum(min);
    setMaximum(max);
}

void RingProgressWidget::setRingColor(const QColor &color)
{
    if (color != m_ringColor) {
        m_ringColor = color;
        update();
    }
}

void RingProgressWidget::setBackgroundColor(const QColor &color)
{
    if (color != m_backgroundColor) {
        m_backgroundColor = color;
        update();
    }
}

void RingProgressWidget::setTextColor(const QColor &color)
{
    if (color != m_textColor) {
        m_textColor = color;
        update();
    }
}

void RingProgressWidget::setRingWidth(int width)
{
    if (width != m_ringWidth && width > 0) {
        m_ringWidth = width;
        update();
    }
}

QSize RingProgressWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize RingProgressWidget::sizeHint() const
{
    return QSize(150, 150);
}

void RingProgressWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 计算中心点和半径
    int side = qMin(width(), height());
    QPointF center(width() / 2.0, height() / 2.0);
    double outerRadius = (side - m_ringWidth) / 2.0;
    
    // 绘制背景圆
    if (m_backgroundColor != Qt::transparent) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(m_backgroundColor);
        painter.drawEllipse(center, outerRadius, outerRadius);
    }
    
    // 计算进度比例和角度
    double progress = qBound(0.0, (m_value - m_minimum) * 1.0 / (m_maximum - m_minimum), 1.0);
    int spanAngle = -progress * 360 * 16;  // QT中角度以1/16度为单位，负号表示顺时针
    
    // 绘制基础圆环（未完成部分）
    painter.setPen(QPen(QColor(m_ringColor).lighter(150), m_ringWidth));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(center, outerRadius, outerRadius);
    
    // 绘制进度圆环（已完成部分）
    QPen pen(m_ringColor, m_ringWidth);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    
    // 从顶部(90°)开始，顺时针绘制
    int startAngle = 90 * 16;  // QT中0°在3点钟方向，所以顶部是90°
    painter.drawArc(QRectF(center.x() - outerRadius, center.y() - outerRadius,
                          outerRadius * 2, outerRadius * 2),
                  startAngle, spanAngle); // QPainterPath是绘制封闭路径的
    
    // 绘制文本
    QString text = QString::number(progress * 100, 'f', 1) + "%";
    QFont font = painter.font();
    font.setPointSize(outerRadius / 3.0);
    painter.setFont(font);
    painter.setPen(m_textColor);
    painter.drawText(QRectF(center.x() - outerRadius, center.y() - outerRadius, 
                          outerRadius * 2, outerRadius * 2), 
                   Qt::AlignCenter, text);
}