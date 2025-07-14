#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QPainter>

class DashBoard : public QWidget
{
    Q_OBJECT
    // 可自定义属性
    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(int precision READ getPrecision WRITE setPrecision)
    Q_PROPERTY(QString unit READ getUnit WRITE setUnit)
    Q_PROPERTY(QColor startColor READ getStartColor WRITE setStartColor)
    Q_PROPERTY(QColor endColor READ getEndColor WRITE setEndColor)

public:
    explicit DashBoard(QWidget *parent = nullptr);

    // 设置和获取当前值
    void setValue(double value);
    double getValue() const;

    // 设置和获取最小值
    void setMinValue(double value);
    double getMinValue() const;

    // 设置和获取最大值
    void setMaxValue(double value);
    double getMaxValue() const;

    // 设置和获取精度
    void setPrecision(int precision);
    int getPrecision() const;

    // 设置和获取单位
    void setUnit(const QString &unit);
    QString getUnit() const;

    // 设置和获取起始颜色
    void setStartColor(const QColor &color);
    QColor getStartColor() const;

    // 设置和获取结束颜色
    void setEndColor(const QColor &color);
    QColor getEndColor() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawBackground(QPainter *painter);       // 绘制背景
    void drawScale(QPainter *painter);            // 绘制刻度
    void drawScaleNum(QPainter *painter);         // 绘制刻度值
    void drawPointer(QPainter *painter);          // 绘制指针
    void drawValue(QPainter *painter);            // 绘制当前值
    void drawUnit(QPainter *painter);             // 绘制单位

private:
    double m_minValue;    // 最小值
    double m_maxValue;    // 最大值
    double m_value;       // 当前值
    int m_precision;      // 精度(小数点后位数)
    QString m_unit;       // 单位
    QColor m_startColor;  // 渐变开始颜色
    QColor m_endColor;    // 渐变结束颜色
};

#endif // DASHBOARD_H