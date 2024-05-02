#ifndef EDGE_H
#define EDGE_H

#include "error_codes.h"
#include <cstdio>

struct Edge {
    int from, to;
};

/**
 * @brief readEdge Функция чтения ребра из файла
 * @param [out] edge - ребро
 * @param [in, out] f - файловый указатель
 * @return Код ошибки (0 - успех)
 */
err_t readEdge(Edge &edge, FILE *f);

/**
 * @brief writeEdge Процедура записи ребра в файл
 * @param [in] edge - ребро
 * @param [in, out] f - файловый указатель
 */
void writeEdge(const Edge &edge, FILE *f);

bool checkEdgeIndex(const Edge &edge, int max_n);

#endif // EDGE_H
