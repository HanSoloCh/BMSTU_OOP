#ifndef EDGE_ARR_H
#define EDGE_ARR_H

#include <cstdio>
#include "error_codes.h"
#include "edge.h"

struct EdgesArr {
    int countEdges;
    Edge *edge;
};

EdgesArr initEdgesArr();

bool isEdgesArrRead(const EdgesArr &edgesArr);

err_t createEdgesArr(EdgesArr &edgesArr, FILE *f);

/**
 * @brief freeEdgesArr Процедура освобождения памяти из-под массива ребер
 * @param [in, out] edgesArr - массив ребер
 */
void destroyEdgesArr(EdgesArr &edgesArr);

/**
 * @brief writeEdgesArr Функция записи массива ребер в файл
 * @param [in] edgesArr - массив ребер
 * @param [in, out] f - файловый указатель
 * @return
 */
err_t writeEdgesArr(const EdgesArr &edgesArr, FILE *f);

#endif // EDGE_ARR_H
