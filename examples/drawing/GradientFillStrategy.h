// GradientFillStrategy.h
#ifndef GRADIENTFILLSTRATEGY_H
#define GRADIENTFILLSTRATEGY_H

#include "IFillStrategy.h"

class GradientFillStrategy : public IFillStrategy {
public:
    void fill(QPainter &painter) override {
        QLinearGradient gradient(50, 50, 200, 200);
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::red);
        painter.setBrush(gradient);
    }
};

#endif // GRADIENTFILLSTRATEGY_H
