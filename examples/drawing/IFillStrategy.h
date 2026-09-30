// IFillStrategy.h
#ifndef IFILLSTRATEGY_H
#define IFILLSTRATEGY_H

#include <QPainter>

class IFillStrategy {
public:
    virtual ~IFillStrategy() = default;
    virtual void fill(QPainter &painter) = 0;
};

#endif // IFILLSTRATEGY_H
