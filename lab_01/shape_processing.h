#ifndef SHAPE_PROCESSING_H
#define SHAPE_PROCESSING_H

#include "error_codes.h"

#include <QGraphicsScene>

enum command_t {
    INIT,
    MOVE,
    SCALE,
    ROTATE,
    SAVE,
    DRAW,
    DELETE,
};

struct MoveData {
    double dx;
    double dy;
    double dz;
};

struct ScaleData {
    double kx;
    double ky;
    double kz;
};

struct RotateData {
    double ox;
    double oy;
    double oz;
};

struct Drawer {
    QGraphicsScene *scene;
    QPen pen;
};

struct ShapeAction {
    command_t command;
    Drawer drawer;

    union {
        MoveData moveData;
        ScaleData scaleData;
        RotateData rotateData;
        const char *fileName;
    };
};

/**
 * @brief shapeProcessing Функция обработки фигуры
 * @param [in, out] drawer - отрисовщик
 * @param [in] shapeAction - действие над фигурой
 * @return Код ошибки (0 - успех)
 */
err_t shapeProcessing(ShapeAction &shapeAction);

/**
 * @brief initDrawer Функция инициализации отрисовщика
 * @param [in] color - цвет фигуры
 * @param [in] scene - сцена
 * @return Отрисовщик
 */
Drawer &initDrawer(const char *color, QGraphicsScene *scene);

#endif // SHAPE_PROCESSING_H
