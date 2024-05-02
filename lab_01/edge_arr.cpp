#include "edge_arr.h"

#include <cstdlib>

#include "error_codes.h"
#include "edge.h"

EdgesArr initEdgesArr() {
    EdgesArr edgesArr = {
        .countEdges = 0,
        .edge = nullptr,
    };
    return edgesArr;
}

bool isEdgesArrRead(const EdgesArr &edgesArr) {
    return edgesArr.countEdges > 0;
}

err_t allocEdgesArr(Edge *&edgesArr, int countEdges) {
    if (countEdges <= 0)
        return ERR_RANGE;
    err_t rc = OK;
    Edge *tmpArr = (Edge *)malloc(countEdges * sizeof(Edge));
    if (tmpArr == nullptr) {
        rc = ERR_DYN_MEM;
    } else
        edgesArr = tmpArr;
    return rc;
}

void destroyEdgesArr(EdgesArr &edgesArr) {
    free(edgesArr.edge);
    edgesArr.edge = nullptr;
    edgesArr.countEdges = 0;
}

static err_t readEdgesCount(int &n, FILE *f) {
    err_t rc = OK;
    if (fscanf(f, "%d", &n) != 1)
        rc = ERR_IO;
    else if (n <= 0)
        rc = ERR_RANGE;
    return rc;
}

static err_t readEdgesArrWithSize(Edge *edges, int n, FILE *f) {
    err_t rc = OK;
    int i;
    for (i = 0; rc == OK && i < n; ++i)
        rc = readEdge(edges[i], f);
    return rc;
}

err_t createEdgesArr(EdgesArr &edgesArr, FILE *f) {
    err_t rc = readEdgesCount(edgesArr.countEdges, f);
    if (rc == OK) {
        rc = allocEdgesArr(edgesArr.edge, edgesArr.countEdges);
        if (rc == OK) {
            rc = readEdgesArrWithSize(edgesArr.edge, edgesArr.countEdges, f);
            if (rc != OK)
                free(edgesArr.edge);
        }
    }
    return rc;
}

static void writeEdgesArrWithSize(const Edge *edges, int n, FILE *f) {
    for (int i = 0; i < n; ++i)
        writeEdge(edges[i], f);
}

static void writeEdgesArrSize(int size, FILE *f) {
    fprintf(f, "%d\n", size);
}

err_t writeEdgesArr(const EdgesArr &edgesArr, FILE *f) {
    if (edgesArr.countEdges == 0)
        return ERR_NO_DATA;
    writeEdgesArrSize(edgesArr.countEdges, f);
    writeEdgesArrWithSize(edgesArr.edge, edgesArr.countEdges, f);
    return OK;
}
