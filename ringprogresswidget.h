// ringprogresswidget.h
#ifndef RINGPROGRESSWIDGET_H
#define RINGPROGRESSWIDGET_H

#include <QWidget>
#include <QPainter>

class RingProgressWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(QColor ringColor READ ringColor WRITE setRingColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(int ringWidth READ ringWidth WRITE setRingWidth)
    
public:
    explicit RingProgressWidget(QWidget *parent = nullptr);
    
    // 属性访问器
    int value() const { return m_value; }
    int minimum() const { return m_minimum; }
    int maximum() const { return m_maximum; }
    QColor ringColor() const { return m_ringColor; }
    QColor backgroundColor() const { return m_backgroundColor; }
    QColor textColor() const { return m_textColor; }
    int ringWidth() const { return m_ringWidth; }
    
    // 属性设置器
    void setValue(int value);
    void setMinimum(int min);
    void setMaximum(int max);
    void setRange(int min, int max);
    void setRingColor(const QColor &color);
    void setBackgroundColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setRingWidth(int width);
    
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    
signals:
    void valueChanged(int value);
    
protected:
    void paintEvent(QPaintEvent *event) override;
    
private:
    int m_value;
    int m_minimum;
    int m_maximum;
    QColor m_ringColor;
    QColor m_backgroundColor;
    QColor m_textColor;
    int m_ringWidth;
};

#endif // RINGPROGRESSWIDGET_H