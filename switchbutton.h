#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QColor>
#include <QPropertyAnimation>
#include <QWidget>

class QKeyEvent;
class QMouseEvent;
class QResizeEvent;

class SwitchButton : public QWidget {
    Q_OBJECT
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY toggled)
    Q_PROPERTY(QColor checkedColor READ checkedColor WRITE setCheckedColor)
    Q_PROPERTY(QColor uncheckedColor READ uncheckedColor WRITE setUncheckedColor)
    Q_PROPERTY(QColor thumbColor READ thumbColor WRITE setThumbColor)
    Q_PROPERTY(qreal thumbPosition READ thumbPosition WRITE setThumbPosition)
public:
    explicit SwitchButton(QWidget *parent = nullptr);
    bool isChecked() const { return m_checked; }
    QColor checkedColor() const { return m_checkedColor; }
    QColor uncheckedColor() const { return m_uncheckedColor; }
    QColor thumbColor() const { return m_thumbColor; }
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
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    void updateThumbPosition();
    qreal thumbPosition() const { return m_thumbPosition; }
    void setThumbPosition(qreal position) { m_thumbPosition = position; update(); }
    bool m_checked = false;
    QColor m_checkedColor = QColor(100, 184, 255);
    QColor m_uncheckedColor = QColor(200, 200, 200);
    QColor m_thumbColor = Qt::white;
    QPropertyAnimation *m_animation = nullptr;
    qreal m_thumbPosition = 0;
};
#endif
