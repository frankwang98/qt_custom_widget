#include "dashboard.h"
#include <QPainter>
#include <QConicalGradient>
#include <QtMath>

DashBoard::DashBoard(QWidget *parent) : QWidget(parent)
{
    // 初始化默认值
    m_minValue = 0;
    m_maxValue = 100;
    m_value = 0;
    m_precision = 1;
    m_unit = "km/h";
    m_startColor = Qt::green;
    m_endColor = Qt::red;
}

void DashBoard::setValue(double value)
{
    // 限制数值范围
    if(value < m_minValue) {
        m_value = m_minValue;
    } else if(value > m_maxValue) {
        m_value = m_maxValue;
    } else {
        m_value = value;
    }
    update(); // 触发重绘
}

double DashBoard::getValue() const
{
    return m_value;
}

void DashBoard::setMinValue(double value)
{
    m_minValue = value;
    update();
}

double DashBoard::getMinValue() const
{
    return m_minValue;
}

void DashBoard::setMaxValue(double value)
{
    m_maxValue = value;
    update();
}

double DashBoard::getMaxValue() const
{
    return m_maxValue;
}

void DashBoard::setPrecision(int precision)
{
    m_precision = precision;
    update();
}

int DashBoard::getPrecision() const
{
    return m_precision;
}

void DashBoard::setUnit(const QString &unit)
{
    m_unit = unit;
    update();
}

QString DashBoard::getUnit() const
{
    return m_unit;
}

void DashBoard::setStartColor(const QColor &color)
{
    m_startColor = color;
    update();
}

QColor DashBoard::getStartColor() const
{
    return m_startColor;
}

void DashBoard::setEndColor(const QColor &color)
{
    m_endColor = color;
    update();
}

QColor DashBoard::getEndColor() const
{
    return m_endColor;
}

void DashBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 抗锯齿
    
    // 计算绘制区域
    int side = qMin(width(), height());
    painter.translate(width() / 2, height() / 2);  // 坐标原点移到中心
    painter.scale(side / 200.0, side / 200.0);     // 缩放
    
    // 绘制各部件
    drawBackground(&painter);
    drawScale(&painter);
    drawScaleNum(&painter);
    drawPointer(&painter);
    drawValue(&painter);
    drawUnit(&painter);
}

void DashBoard::drawBackground(QPainter *painter)
{
    painter->save();
    
    // 绘制外圆
    painter->setPen(Qt::NoPen);
    QRadialGradient radialGradient(0, 0, 100);
    radialGradient.setColorAt(0, QColor(100, 100, 100));
    radialGradient.setColorAt(1, QColor(50, 50, 50));
    painter->setBrush(radialGradient);
    painter->drawEllipse(-90, -90, 180, 180);
    
    // 绘制内圆
    painter->setBrush(QColor(30, 30, 30));
    painter->drawEllipse(-80, -80, 160, 160);
    
    painter->restore();
}

void DashBoard::drawScale(QPainter *painter)
{
    painter->save();
    
    // 从正上方(90度)开始绘制，逆时针方向
    painter->rotate(90);
    
    int totalSteps = (m_maxValue - m_minValue) * 1;  // 总刻度数(分度值为1)
    double angleStep = 360.0 / totalSteps;           // 每个刻度之间的角度
    
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    
    for(int i = 0; i <= totalSteps; i++) {
        // 设置刻度线颜色和粗细
        if(i % 10 == 0) {  // 大刻度(每10个小刻度)
            pen.setWidthF(2.0);
            pen.setColor(Qt::white);
        } else if(i % 5 == 0) {  // 中刻度(每5个小刻度)
            pen.setWidthF(1.5);
            pen.setColor(Qt::lightGray);
        } else {  // 小刻度
            pen.setWidthF(1.0);
            pen.setColor(Qt::gray);
        }
        
        painter->setPen(pen);
        
        // 绘制刻度线
        if(i % 10 == 0) {  // 大刻度线较长
            painter->drawLine(60, 0, 75, 0);
        } else if(i % 5 == 0) {  // 中刻度线中等长度
            painter->drawLine(65, 0, 75, 0);
        } else {  // 小刻度线较短
            painter->drawLine(70, 0, 75, 0);
        }
        
        painter->rotate(angleStep);  // 使用正角度表示逆时针旋转
    }
    
    painter->restore();
}

void DashBoard::drawScaleNum(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::white);
    
    int totalSteps = (m_maxValue - m_minValue) * 1;  // 总刻度数(分度值为1)
    double angleStep = 360.0 / totalSteps;           // 每个刻度之间的角度
    
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(4);
    painter->setFont(font);
    
    // 只在大刻度位置显示数字(每10个小刻度)，但不显示最后一个(与0重合)
    for(int i = 0; i < totalSteps; i += 10) {
        // 计算数值
        double value = m_minValue + i;
        QString text = QString::number(value, 'f', m_precision);
        
        // 计算位置(从正上方开始，逆时针)
        double angle = 90 - angleStep * i;  // 从90度开始，逆时针递增
        double radian = qDegreesToRadians(angle);
        int x = 85 * qCos(radian);
        int y = -85 * qSin(radian);  // y坐标取反，因为Qt的y轴向下
        
        QRect textRect(x - 15, y - 10, 30, 20);
        painter->drawText(textRect, Qt::AlignCenter, text);
    }
    
    painter->restore();
}

void DashBoard::drawPointer(QPainter *painter)
{
    painter->save();
    
    // 计算指针角度 (0度在正上方90度位置，逆时针方向增加)
    double ratio = (m_value - m_minValue) / (m_maxValue - m_minValue);
    double angle = 270 + ratio * 360;  // 从90度开始，逆时针递增
    
    // 标准化角度到0-360度范围
    while(angle >= 360) angle -= 360;
    while(angle < 0) angle += 360;
    
    painter->rotate(angle);
    
    // 绘制指针
    QPolygon points;
    points.append(QPoint(0, 5));
    points.append(QPoint(60, 0));
    points.append(QPoint(0, -5));
    
    QRadialGradient radialGradient(0, 0, 60);
    radialGradient.setColorAt(0, QColor(255, 100, 100));
    radialGradient.setColorAt(1, QColor(200, 50, 50));
    
    painter->setBrush(radialGradient);
    painter->setPen(Qt::NoPen);
    painter->drawPolygon(points);
    
    // 绘制指针中心点
    painter->setBrush(Qt::red);
    painter->drawEllipse(-5, -5, 10, 10);
    
    painter->restore();
}

void DashBoard::drawValue(QPainter *painter)
{
    painter->save();
    
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(12);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(Qt::white);
    
    QString text = QString::number(m_value, 'f', m_precision);
    QRect textRect(-50, 30, 100, 30);
    painter->drawText(textRect, Qt::AlignCenter, text);
    
    painter->restore();
}

void DashBoard::drawUnit(QPainter *painter)
{
    painter->save();
    
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(8);
    painter->setFont(font);
    painter->setPen(Qt::black);
    
    QRect textRect(30, 70, 100, 20); // 单位位置
    painter->drawText(textRect, Qt::AlignCenter, m_unit);
    
    painter->restore();
}