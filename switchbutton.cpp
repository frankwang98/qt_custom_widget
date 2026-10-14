#include "switchbutton.h"
#include <QEasingCurve>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QStyle>

SwitchButton::SwitchButton(QWidget *parent) : QWidget(parent) {
    setMinimumSize(50, 30);
    setFocusPolicy(Qt::StrongFocus);
    setAccessibleName(tr("Switch"));
    m_animation = new QPropertyAnimation(this, "thumbPosition", this);
    m_animation->setDuration(200);
    m_animation->setEasingCurve(QEasingCurve::InOutQuad);
}
void SwitchButton::setChecked(bool checked) {
    if (m_checked == checked) return;
    m_checked = checked;
    updateThumbPosition();
    update();
    emit toggled(m_checked);
}
void SwitchButton::setCheckedColor(const QColor &color) {
    if (m_checkedColor != color) { m_checkedColor = color; update(); }
}
void SwitchButton::setUncheckedColor(const QColor &color) {
    if (m_uncheckedColor != color) { m_uncheckedColor = color; update(); }
}
void SwitchButton::setThumbColor(const QColor &color) {
    if (m_thumbColor != color) { m_thumbColor = color; update(); }
}
QSize SwitchButton::sizeHint() const { return QSize(60, 30); }
void SwitchButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_checked ? m_checkedColor : m_uncheckedColor);
    const QRectF track = QRectF(rect()).adjusted(1, 1, -1, -1);
    const qreal radius = track.height() / 2.0;
    painter.drawRoundedRect(track, radius, radius);
    const qreal thumbRadius = qMax(2.0, (track.height() - 6.0) / 2.0);
    const qreal left = track.left() + 3.0 + thumbRadius;
    const qreal right = track.right() - 3.0 - thumbRadius;
    const qreal x = left + m_thumbPosition * qMax(0.0, right - left);
    painter.setBrush(m_thumbColor);
    painter.drawEllipse(QPointF(x, track.center().y()), thumbRadius, thumbRadius);
    if (hasFocus()) {
        QStyleOptionFocusRect option;
        option.initFrom(this);
        option.rect = rect().adjusted(1, 1, -1, -1);
        style()->drawPrimitive(QStyle::PE_FrameFocusRect, &option, &painter, this);
    }
}
void SwitchButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && isEnabled()) {
        setFocus(Qt::MouseFocusReason);
        setChecked(!m_checked);
        event->accept();
        return;
    }
    QWidget::mousePressEvent(event);
}
void SwitchButton::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space || event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        if (!event->isAutoRepeat()) setChecked(!m_checked);
        event->accept();
        return;
    }
    QWidget::keyPressEvent(event);
}
void SwitchButton::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    if (m_animation->state() == QAbstractAnimation::Running) m_animation->stop();
    m_thumbPosition = m_checked ? 1.0 : 0.0;
}
void SwitchButton::updateThumbPosition() {
    m_animation->stop();
    m_animation->setStartValue(m_thumbPosition);
    m_animation->setEndValue(m_checked ? 1.0 : 0.0);
    m_animation->start();
}
