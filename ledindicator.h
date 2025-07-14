// ledindicator.h
#ifndef LEDINDICATOR_H
#define LEDINDICATOR_H

#include <QWidget>

class LedIndicator : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool on READ isOn WRITE setOn NOTIFY stateChanged)
    Q_PROPERTY(QColor onColor READ onColor WRITE setOnColor)
    Q_PROPERTY(QColor offColor READ offColor WRITE setOffColor)
    Q_PROPERTY(int size READ size WRITE setSize)
    
public:
    explicit LedIndicator(QWidget *parent = nullptr);
    
    // 属性访问器
    bool isOn() const { return m_on; }
    QColor onColor() const { return m_onColor; }
    QColor offColor() const { return m_offColor; }
    int size() const { return m_size; }
    
    // 属性设置器
    void setOn(bool on);
    void setOnColor(const QColor &color);
    void setOffColor(const QColor &color);
    void setSize(int size);
    
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    
signals:
    void stateChanged(bool on);
    
protected:
    void paintEvent(QPaintEvent *event) override;
    
private:
    bool m_on;
    QColor m_onColor;
    QColor m_offColor;
    int m_size;
    
    void drawLed(QPainter &painter, const QRectF &rect, const QColor &color);
};

#endif // LEDINDICATOR_H