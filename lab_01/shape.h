#ifndef SHAPE_H
#define SHAPE_H

#include "point_arr.h"
#include "edge_arr.h"
#include "error_codes.h"

struct Shape {
    EdgesArr edgesArr;
    PointsArr pointsArr;
};

/**
 * @brief shapeInit Функция инициализации фигуры
 * @return Фигура
 */
Shape initShape();

bool isShapeRead(const Shape &shape);

bool isValid(const Shape &shape);

/**
 * @brief freeShape Процедура освободления памяти из-под фигуры
 * @param [in, out] shape - фигура
 */
void destroyShape(Shape &shape);

/**
 * @brief createShapeFromFile Функция создания фигуры из файла
 * @param [out] shape - фигура
 * @param [in, out] file - файловый указатель
 * @return Код ошибки (0 - успех)
 */
err_t createShapeFromFile(Shape &shape, FILE *file);

/**
 * @brief createShapeFromFileEx Функция создания фигуры из файла (расширенная)
 * @param [out] shape - фигура
 * @param [in] fileName - имя файла
 * @return Код ошибки (0 - успех)
 */
err_t createShapeFromFileEx(Shape &shape, const char *fileName);

/**
 * @brief saveShapeToFile Процедура сохранения фигуры в файл
 * @param [in] shape - фигура
 * @param [in, out] file - файловый указатель
 */
err_t writeShapeToFile(const Shape &shape, FILE *file);

/**
 * @brief saveShapeToFileEx Функция сохранения фигуры в файл (расширенная)
 * @param [in] shape - фигура
 * @param [in] fileName - имя файла
 * @return
 */
err_t writeShapeToFileEx(const Shape &shape, const char *fileName);

err_t moveShape(Shape &shape, const MoveData &moveData);

err_t scaleShape(Shape &shape, const ScaleData &scaleData);

err_t rotateShape(Shape &shape, const RotateData &rotateData);

#endif // SHAPE_H
