// switchbutton.h
#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QMouseEvent>

class SwitchButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY toggled)
    Q_PROPERTY(QColor checkedColor READ checkedColor WRITE setCheckedColor)
    Q_PROPERTY(QColor uncheckedColor READ uncheckedColor WRITE setUncheckedColor)
    Q_PROPERTY(QColor thumbColor READ thumbColor WRITE setThumbColor)
    Q_PROPERTY(qreal thumbPosition READ thumbPosition WRITE setThumbPosition)
    
public:
    explicit SwitchButton(QWidget *parent = nullptr);
    
    // 属性访问器
    bool isChecked() const { return m_checked; }
    QColor checkedColor() const { return m_checkedColor; }
    QColor uncheckedColor() const { return m_uncheckedColor; }
    QColor thumbColor() const { return m_thumbColor; }
    
    // 属性设置器
    void setChecked(bool checked);
    void setCheckedColor(const QColor &color);
    void setUncheckedColor(const QColor &color);
    void setThumbColor(const QColor &color);
    
    QSize sizeHint() const override;
    
signals:
    void toggled(bool checked);
    
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    
private:
    bool m_checked;
    QColor m_checkedColor;
    QColor m_uncheckedColor;
    QColor m_thumbColor;
    QPropertyAnimation *m_animation;
    qreal m_thumbPosition;
    
    void updateThumbPosition();

    // 添加thumbPosition属性访问器
    qreal thumbPosition() const { return m_thumbPosition; }
    void setThumbPosition(qreal position) { m_thumbPosition = position; }
};

#endif // SWITCHBUTTON_H