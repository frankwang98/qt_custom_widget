// compasswidget.cpp
#include "compasswidget.h"
#include <cmath>
#include <QPainter>

CompassWidget::CompassWidget(QWidget *parent) : QWidget(parent),
    m_angle(0),
    m_backgroundColor(Qt::black),
    m_pointerColor(Qt::red),
    m_textColor(Qt::white)
{
    setMinimumSize(100, 100);
}

void CompassWidget::setAngle(double angle)
{
    if (angle != m_angle) {
        m_angle = angle;
        update();
        emit angleChanged(m_angle);
    }
}

QSize CompassWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize CompassWidget::sizeHint() const
{
    return QSize(200, 200);
}

void CompassWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    int side = qMin(width(), height());
    QPointF center(width() / 2.0, height() / 2.0);
    double radius = side / 2.0 - 10;
    
    // 绘制背景圆
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_backgroundColor);
    painter.drawEllipse(center, radius, radius);
    
    // 绘制刻度
    painter.setPen(m_textColor);
    for (int i = 0; i < 360; i += 30) {
        double angle = i * M_PI / 180.0;
        QPointF innerPoint(center.x() + (radius - 10) * sin(angle),
                          center.y() - (radius - 10) * cos(angle));
        QPointF outerPoint(center.x() + radius * sin(angle),
                          center.y() - radius * cos(angle));
        painter.drawLine(innerPoint, outerPoint);
        
        if (i % 90 == 0) {
            QString text;
            switch (i) {
            case 0: text = "N"; break;
            case 90: text = "E"; break;
            case 180: text = "S"; break;
            case 270: text = "W"; break;
            }
            
            QFont font = painter.font();
            font.setBold(true);
            painter.setFont(font);
            
            QPointF textPoint(center.x() + (radius - 25) * sin(angle),
                             center.y() - (radius - 25) * cos(angle));
            QRectF textRect(textPoint.x() - 10, textPoint.y() - 10, 20, 20);
            painter.drawText(textRect, Qt::AlignCenter, text);
        }
    }
    
    // 修正后的指针绘制
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_pointerColor);
    
    double pointerAngle = m_angle * M_PI / 180.0;
    QPolygonF pointer;
    pointer << QPointF(center.x() + radius * sin(pointerAngle),
                  center.y() - radius * cos(pointerAngle))
            << QPointF(center.x() + radius * 0.2 * sin(pointerAngle + M_PI * 0.8),
                  center.y() - radius * 0.2 * cos(pointerAngle + M_PI * 0.8))
            << QPointF(center.x() + radius * 0.2 * sin(pointerAngle + M_PI * 1.2),
                  center.y() - radius * 0.2 * cos(pointerAngle + M_PI * 1.2));
    
    painter.drawPolygon(pointer);
    
    // 绘制中心点
    painter.setBrush(Qt::white);
    painter.drawEllipse(center, 5, 5);
}