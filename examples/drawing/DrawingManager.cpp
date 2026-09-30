// DrawingManager.cpp
#include "DrawingManager.h"

DrawingManager* DrawingManager::instance_ = nullptr; // 定义静态成员变量

DrawingManager* DrawingManager::instance() {
    if (!instance_) {
        instance_ = new DrawingManager();
    }
    return instance_;
}

void DrawingManager::addShape(const QString &shapeType, const QString &fillType) {
    IShape* shape = ShapeFactory::createShape(shapeType);
    IFillStrategy* fillStrategy = nullptr;

    if (fillType.compare("Solid", Qt::CaseInsensitive) == 0) {
        fillStrategy = new SolidFillStrategy();
    } else if (fillType.compare("Gradient", Qt::CaseInsensitive) == 0) {
        fillStrategy = new GradientFillStrategy();
    } else {
        qWarning() << "Unknown fill type:" << fillType;
        return;
    }

    shapes_.append(new ShapeDrawer(shape, fillStrategy));
}

void DrawingManager::drawShapes(QPainter &painter) {
    for (auto shapeDrawer : shapes_) {
        shapeDrawer->drawShape(painter);
    }
}

void DrawingManager::addShapeAtPosition(const QString &shapeType, const QString &fillType, int x, int y)
{
    IShape* shape = ShapeFactory::createShapeAtPosition(shapeType, x, y);
    IFillStrategy* fillStrategy = nullptr;

    if (fillType.compare("Solid", Qt::CaseInsensitive) == 0) {
        fillStrategy = new SolidFillStrategy();
    } else if (fillType.compare("Gradient", Qt::CaseInsensitive) == 0) {
        fillStrategy = new GradientFillStrategy();
    } else {
        qWarning() << "Unknown fill type:" << fillType;
        return;
    }

    shapes_.append(new ShapeDrawer(shape, fillStrategy));
}
