// compasswidget.h
#ifndef COMPASSWIDGET_H
#define COMPASSWIDGET_H

#include <QWidget>
#include <QPainter>

class CompassWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double angle READ angle WRITE setAngle NOTIFY angleChanged)
    
public:
    explicit CompassWidget(QWidget *parent = nullptr);
    
    double angle() const { return m_angle; }
    void setAngle(double angle);
    
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    
signals:
    void angleChanged(double angle);
    
protected:
    void paintEvent(QPaintEvent *event) override;
    
private:
    double m_angle;
    QColor m_backgroundColor;
    QColor m_pointerColor;
    QColor m_textColor;
};

#endif // COMPASSWIDGET_H