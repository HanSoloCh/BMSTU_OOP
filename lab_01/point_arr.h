#ifndef POINT_ARR_H
#define POINT_ARR_H

#include <cstdio>

#include "point.h"
#include "error_codes.h"
#include "shape_processing.h"

struct PointsArr {
    int countPoints;
    Point *points;
};

PointsArr initPointsArr();

bool isPointsArrRead(const PointsArr &pointsArr);

err_t createPointsArr(PointsArr &pointsArr, FILE *f);

void destroyPointsArr(PointsArr &pointsArr);

/**
 * @brief writePointsArr Функция созранения массива точек в файл
 * @param [in] pointsArr - массив точек
 * @param [in, out] f - файловый указатель
 * @return
 */
err_t writePointsArr(const PointsArr &pointsArr, FILE *f);

/**
 * @brief pointsArrMove Функция перемещения массива точек
 * @param [in, out] pointsArr - массив точек
 * @param [in] moveData - данные смещения
 * @return
 */
err_t movePointsArr(PointsArr &pointsArr, const MoveData &moveData);

/**
 * @brief rotatePointsArr Функция вращения массива точек
 * @param [in, out] pointsArr - массив точек
 * @param [in] rotateData - данные вращения
 * @return
 */
err_t rotatePointsArr(PointsArr &pointsArr, const RotateData &rotateData);

/**
 * @brief scalePointsArr Функция масштабирования точек
 * @param [in, out] pointsArr - массив точек
 * @param [in] scaleData - данные масштабирования
 * @return
 */
err_t scalePointsArr(PointsArr &pointsArr, const ScaleData &scaleData);

#endif // POINT_ARR_H
