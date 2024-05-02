#ifndef POINT_H
#define POINT_H

#include <cstdio>

#include "error_codes.h"
#include "shape_processing.h"

struct Point {
    double x;
    double y;
    double z;
};

/**
 * @brief readPoint Функция чтения точки из файла
 * @param [out] point - точка
 * @param [in, out] f - файловый указатель
 * @return Код ошибки (0 - успех)
 */
err_t readPoint(Point &point, FILE *f);

/**
 * @brief writePoint Процедура сохранения точки в файл
 * @param [in] point - точка
 * @param [in, out] f - файловый указатель
 */
void writePoint(const Point &point, FILE *f);

/**
 * @brief movePoint Процедура перемещения точки
 * @param [in, out] point - точка
 * @param [in] moveData - данные перемещения
 */
void movePoint(Point &point, const MoveData &moveData);

/**
 * @brief rotatePoint Процедура вращения точки
 * @param [in, out] point - точка
 * @param [in] rotateCenter - центр вращения
 * @param [in] rotateData - данные вращения
 */
void rotatePoint(Point &point, const Point &rotateCenter, const RotateData &rotateData);

/**
 * @brief scalePoint Процедура масштабирования
 * @param [in, out] point - точка
 * @param [in] scaleCenter - центр масштабирования
 * @param [in] scaleData - данные масштабирования
 */
void scalePoint(Point &point, const Point &scaleCenter, const ScaleData &scaleData);

#endif // POINT_H
