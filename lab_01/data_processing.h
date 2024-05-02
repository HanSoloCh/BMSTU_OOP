#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include <QGraphicsScene>

#include "shape_processing.h"

/**
 * @brief dataProcessing Функция инициализации данных для взаимодействия с фигурой
 * @param [in] command - команда
 * @return Ссылка на структуру данных
 */
ShapeAction &dataProcessing(Drawer &srawer, int command, ...);

#endif // DATA_PROCESSING_H
