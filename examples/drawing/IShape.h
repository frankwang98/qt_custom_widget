// IShape.h
#ifndef ISHAPE_H
#define ISHAPE_H

#include <QPainter>

class IShape {
public:
    virtual ~IShape() = default;
    virtual void draw(QPainter &painter) = 0;
};

#endif // ISHAPE_H
