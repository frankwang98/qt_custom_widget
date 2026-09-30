// ShapeDrawer.h
#ifndef SHAPEDRAWER_H
#define SHAPEDRAWER_H

#include "IShape.h"
#include "IFillStrategy.h"
#include <QPainter>

class ShapeDrawer {
public:
    ShapeDrawer(IShape* shape, IFillStrategy* fillStrategy)
        : shape_(shape), fillStrategy_(fillStrategy) {}

    void drawShape(QPainter &painter) {
        fillStrategy_->fill(painter);
        shape_->draw(painter);
    }

private:
    IShape* shape_;
    IFillStrategy* fillStrategy_;
};

#endif // SHAPEDRAWER_H
