// DrawingManager.h
#ifndef DRAWINGMANAGER_H
#define DRAWINGMANAGER_H

#include "ShapeFactory.h"
#include "ShapeDrawer.h"
#include "SolidFillStrategy.h"
#include "GradientFillStrategy.h"
#include <QDebug>
#include <QList>

class DrawingManager {
public:
    static DrawingManager* instance(); // 声明静态成员函数

    void addShape(const QString &shapeType, const QString &fillType);
    void drawShapes(QPainter &painter);
    void addShapeAtPosition(const QString &shapeType, const QString &fillType, int x, int y);

private:
    DrawingManager() = default; // 私有构造函数
    static DrawingManager* instance_;
    QList<ShapeDrawer*> shapes_; // 成员变量
};

#endif // DRAWINGMANAGER_H
