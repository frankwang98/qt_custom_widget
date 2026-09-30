// Rectangle.h
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "IShape.h"

class Rectangle : public IShape {
public:
    Rectangle(int x, int y) : x_(x), y_(y) {}

    void draw(QPainter &painter) override {
        painter.setBrush(Qt::green);
        painter.drawRect(x_, y_, 200, 100);
    }

private:
    int x_, y_;
};

#endif // RECTANGLE_H
