#include "data_processing.h"

#include <cstdarg>

#include "shape_processing.h"

static void loadDataForShapeInitAndSave(ShapeAction &shapeData, const char *fileName, int command);
static void laodDataForShapeDelete(ShapeAction &shapeData);
static void loadDataForShapeDraw(ShapeAction &shapeData, Drawer &drawer);

static MoveData moveDataInit(double dx, double dy, double dz);
static void loadDataForShapeMove(ShapeAction &shapeData, double dx, double dy, double dz);

static RotateData rotateDataInit(double ox, double oy, double oz);
static void loadDataForShapeRotate(ShapeAction &shapeData, double ox, double oy, double oz);

static ScaleData scaleDataInit(double kx, double ky, double kz);
static void loadDataForShapeScale(ShapeAction &shapeData, double kx, double ky, double kz);


ShapeAction &dataProcessing(Drawer &drawer, int command, ...) {
    static ShapeAction shapeData;
    va_list args;
    va_start(args, command);
    switch (command) {
    case SAVE:
    case INIT: {
        const char *fileName = va_arg(args, const char *);
        loadDataForShapeInitAndSave(shapeData, fileName, command);
        break;
    }
    case MOVE: {
        double dx = va_arg(args, double);
        double dy = va_arg(args, double);
        double dz = va_arg(args, double);
        loadDataForShapeMove(shapeData, dx, dy, dz);
        break;
    }
    case ROTATE: {
        double ox = va_arg(args, double);
        double oy = va_arg(args, double);
        double oz = va_arg(args, double);
        loadDataForShapeRotate(shapeData, ox, oy, oz);
        break;
    }
    case SCALE: {
        double kx = va_arg(args, double);
        double ky = va_arg(args, double);
        double kz = va_arg(args, double);
        loadDataForShapeScale(shapeData, kx, ky, kz);
        break;
    }
    case DRAW:
        loadDataForShapeDraw(shapeData, drawer);
        break;
    case DELETE:
        laodDataForShapeDelete(shapeData);
        break;
    }
    va_end(args);
    return shapeData;
}

static void loadDataForShapeInitAndSave(ShapeAction &shapeData, const char *fileName, int command) {
    shapeData.command = (command_t)command;
    shapeData.fileName = fileName;
}

static void loadDataForShapeMove(ShapeAction &shapeData, double dx, double dy, double dz) {
    shapeData.command = MOVE;
    shapeData.moveData = moveDataInit(dx, dy, dz);
}

static void loadDataForShapeRotate(ShapeAction &shapeData, double ox, double oy, double oz) {
    shapeData.command = ROTATE;
    shapeData.rotateData = rotateDataInit(ox, oy, oz);
}

static void loadDataForShapeScale(ShapeAction &shapeData, double kx, double ky, double kz) {
    shapeData.command = SCALE;
    shapeData.scaleData = scaleDataInit(kx, ky, kz);
}

static void laodDataForShapeDelete(ShapeAction &shapeData) {
    shapeData.command = DELETE;
}

static void loadDataForShapeDraw(ShapeAction &shapeData, Drawer &drawer) {
    shapeData.command = DRAW;
    shapeData.drawer = drawer;
}

static MoveData moveDataInit(double dx, double dy, double dz) {
    static MoveData moveData;
    moveData.dx = dx;
    moveData.dy = dy;
    moveData.dz = dz;
    return moveData;
}

static RotateData rotateDataInit(double ox, double oy, double oz) {
    static RotateData rotateData;
    rotateData.ox = ox;
    rotateData.oy = oy;
    rotateData.oz = oz;
    return rotateData;
}

static ScaleData scaleDataInit(double kx, double ky, double kz) {
    static ScaleData scaleData;
    scaleData.kx = kx;
    scaleData.ky = ky;
    scaleData.kz = kz;
    return scaleData;
}
