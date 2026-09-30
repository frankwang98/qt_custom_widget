// ShapeFactory.h
#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "Circle.h"
#include "Rectangle.h"

class ShapeFactory {
public:
    static IShape* createShapeAtPosition(const QString &type, int x, int y) {
        if (type == "Circle") {
            return new Circle(x, y);
        } else if (type == "Rectangle") {
            return new Rectangle(x, y);
        }
        return nullptr;
    }

    static IShape* createShape(const QString &type) {
        return createShapeAtPosition(type, 0, 0);
    }
};

#endif // SHAPEFACTORY_H
