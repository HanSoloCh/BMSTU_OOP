#ifndef SHAPE_DRAW_H
#define SHAPE_DRAW_H

#include "shape.h"

/**
 * @brief drawShape Функция отрисовки фигуры
 * @param [in] shape - фигура
 * @param [in, out] drawer - отрисовщик
 * @return
 */
err_t drawShape(const Shape &shape, Drawer &drawer);

#endif // SHAPE_DRAW_H
