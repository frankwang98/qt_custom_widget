// SolidFillStrategy.h
#ifndef SOLIDFILLSTRATEGY_H
#define SOLIDFILLSTRATEGY_H

#include "IFillStrategy.h"

class SolidFillStrategy : public IFillStrategy {
public:
    void fill(QPainter &painter) override {
        painter.setBrush(Qt::SolidPattern);
    }
};

#endif // SOLIDFILLSTRATEGY_H
