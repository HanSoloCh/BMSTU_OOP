#include "shape.h"

#include "error_codes.h"
#include "point_arr.h"
#include "edge_arr.h"

Shape initShape() {
    Shape shape {
        .edgesArr = initEdgesArr(),
        .pointsArr = initPointsArr(),
    };
    return shape;
}

bool isShapeRead(const Shape &shape) {
    return isPointsArrRead(shape.pointsArr) && isEdgesArrRead(shape.edgesArr);
}

bool checkEdgesArrIndex(const EdgesArr &edgesArr, int max_n) {
    bool isValid = true;
    for (int i = 0; i < edgesArr.countEdges && isValid; ++i)
        isValid = checkEdgeIndex(edgesArr.edge[i], max_n);
    return isValid;
}

bool isAllEsgesValid(const EdgesArr &edgesArr, const PointsArr &pointsArr) {
    return checkEdgesArrIndex(edgesArr, pointsArr.countPoints);
}

bool isValid(const Shape &shape) {
    return isAllEsgesValid(shape.edgesArr, shape.pointsArr);
}

void destroyShape(Shape &shape) {
    destroyPointsArr(shape.pointsArr);
    destroyEdgesArr(shape.edgesArr);
}

static void copyShape(Shape &dst, Shape &src) {
    dst = src;
}

err_t createShapeFromFile(Shape &shape, FILE *file) {
    err_t rc = OK;
    rc = createPointsArr(shape.pointsArr, file);
    if (rc == OK) {
        rc = createEdgesArr(shape.edgesArr, file);
        if (rc != OK)
            destroyPointsArr(shape.pointsArr);
    }
    return rc;
}

err_t createShapeFromFileEx(Shape &shape, const char *fileName) {
    err_t rc = OK;
    FILE *file = fopen(fileName, "r");

    if (file == nullptr)
        rc = ERR_FILE;
    else {
        Shape tmpShape = initShape();
        rc = createShapeFromFile(tmpShape, file);
        fclose(file);
        if (rc == OK) {
            if (isValid(tmpShape)) {
                destroyShape(shape);
                copyShape(shape, tmpShape);
            } else {
                rc = ERR_IO;
                destroyShape(tmpShape);
            }
        }
    }

    return rc;
}

static err_t wtiteShapeToFile(const Shape &shape, FILE *file) {
    err_t rc = writePointsArr(shape.pointsArr, file);
    if (rc == OK)
        rc = writeEdgesArr(shape.edgesArr, file);
    return rc;
}

err_t writeShapeToFileEx(const Shape &shape, const char *fileName) {
    err_t rc = OK;
    FILE *file = fopen(fileName, "w");
    if (file == nullptr)
        rc = ERR_FILE;
    else {
        rc = wtiteShapeToFile(shape, file);
        fclose(file);
    }
    return rc;
}

err_t moveShape(Shape &shape, const MoveData &moveData) {
    return movePointsArr(shape.pointsArr, moveData);
}

err_t scaleShape(Shape &shape, const ScaleData &scaleData){
    return scalePointsArr(shape.pointsArr, scaleData);
}

err_t rotateShape(Shape &shape, const RotateData &rotateData) {
    return rotatePointsArr(shape.pointsArr, rotateData);
}
