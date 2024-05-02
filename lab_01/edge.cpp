#include "edge.h"

#include <cstdio>

#include "error_codes.h"

err_t readEdge(Edge &edge, FILE *f) {
    err_t rc = OK;
    if (fscanf(f, "%d %d", &edge.from, &edge.to) != 2)
        rc = ERR_IO;

    return rc;
}

void writeEdge(const Edge &edge, FILE *f) {
    fprintf(f, "%d %d\n", edge.from, edge.to);
}

bool checkEdgeIndex(const Edge &edge, int max_n) {
    return edge.to < max_n && edge.from < max_n;
}
