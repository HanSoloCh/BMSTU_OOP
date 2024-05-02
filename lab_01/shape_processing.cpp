#include "shape_processing.h"

#include <QGraphicsScene>
#include <qdebug.h>

#include "shape.h"
#include "shape_draw.h"
#include "error_codes.h"

err_t shapeProcessing(ShapeAction &shapeAction) {
    static Shape shape = initShape();
    err_t rc = OK;
    switch (shapeAction.command) {
    case INIT:
        rc = createShapeFromFileEx(shape, shapeAction.fileName);
        break;
    case SAVE:
        rc = writeShapeToFileEx(shape, shapeAction.fileName);
        break;
    case MOVE:
        rc = moveShape(shape, shapeAction.moveData);
        break;
    case SCALE:
        rc = scaleShape(shape, shapeAction.scaleData);
        break;
    case ROTATE:
        rc = rotateShape(shape, shapeAction.rotateData);
        break;
    case DRAW:
        rc = drawShape(shape, shapeAction.drawer);
        break;
    case DELETE:
        destroyShape(shape);
        break;
    default:
        rc = UNKNOWN_COMMAND;
        break;
    }
    return rc;
}

Drawer &initDrawer(const char *color, QGraphicsScene *scene) {
    static Drawer drawer;
    drawer.pen = QPen(color);
    drawer.scene = scene;
    return drawer;
}


