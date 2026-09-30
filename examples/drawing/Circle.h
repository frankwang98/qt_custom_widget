// Circle.h
#ifndef CIRCLE_H
#define CIRCLE_H

#include "IShape.h"

class Circle : public IShape {
public:
    Circle(int x, int y) : x_(x), y_(y) {}

    void draw(QPainter &painter) override {
        painter.setBrush(Qt::blue);
        painter.drawEllipse(x_, y_, 100, 100);
    }

private:
    int x_, y_;
};

#endif // CIRCLE_H
