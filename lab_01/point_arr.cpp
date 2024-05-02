#include "point_arr.h"

#include <cstdlib>

#include "error_codes.h"
#include "point.h"
#include "shape_processing.h"

PointsArr initPointsArr() {
    PointsArr pointsArr {
        .countPoints = 0,
        .points = nullptr,
    };
    return pointsArr;
}

bool isPointsArrRead(const PointsArr &pointsArr) {
    return pointsArr.countPoints > 0;
}

err_t allocPointsArr(Point *&pointsArr, int countPoints) {
    err_t rc = OK;
    if (countPoints <= 0)
        rc = ERR_RANGE;
    else {
        Point *tmpArr = (Point *)malloc(countPoints * sizeof(Point));
        if (tmpArr == nullptr) {
            rc = ERR_DYN_MEM;
        } else {
            pointsArr = tmpArr;
        }
    }
    return rc;
}

void destroyPointsArr(PointsArr &pointsArr) {
    free(pointsArr.points);
    pointsArr.points = nullptr;
    pointsArr.countPoints = 0;
}

static err_t readPointsSize(int &size, FILE *f) {
    err_t rc = OK;
    if (fscanf(f, "%d", &size) != 1)
        rc = ERR_IO;
    else if (size <= 0)
        rc = ERR_RANGE;
    return rc;
}

static err_t readPointsArrWithSize(Point *points, int n, FILE *f) {
    err_t rc = OK;
    for (int i = 0; rc == OK && i < n; ++i)
        rc = readPoint(points[i], f);
    return rc;
}

err_t createPointsArr(PointsArr &pointsArr, FILE *f) {
    err_t rc = readPointsSize(pointsArr.countPoints, f);
    if (rc == OK) {
        rc = allocPointsArr(pointsArr.points, pointsArr.countPoints);
        if (rc == OK) {
            rc = readPointsArrWithSize(pointsArr.points, pointsArr.countPoints, f);
            if (rc != OK)
                free(pointsArr.points);
        }
    }
    return rc;
}

static void writePointsArrSize(int size, FILE *f) {
    fprintf(f, "%d\n", size);
}

err_t writePointsArr(const PointsArr &pointsArr, FILE *f) {
    if (pointsArr.countPoints == 0)
        return ERR_NO_DATA;
    writePointsArrSize(pointsArr.countPoints, f);
    for (int i = 0; i < pointsArr.countPoints; ++i)
        writePoint(pointsArr.points[i], f);

    return OK;
}

err_t movePointsArr(PointsArr &pointsArr, const MoveData &moveData) {
    if (pointsArr.points == 0)
        return ERR_NO_DATA;
    for (int i = 0; i < pointsArr.countPoints; ++i)
        movePoint(pointsArr.points[i], moveData);
    return OK;
}

static Point calculateAveragePoint(const Point *points, int countPoints) {
    Point center = {0.0, 0.0, 0.0};

    for (int i = 0; i < countPoints; ++i) {
        center.x += points[i].x;
        center.y += points[i].y;
        center.z += points[i].z;
    }

    center.x /= countPoints;
    center.y /= countPoints;
    center.z /= countPoints;

    return center;
}


err_t rotatePointsArr(PointsArr &pointsArr, const RotateData &rotateData) {
    if (pointsArr.countPoints == 0)
        return ERR_NO_DATA;
    const Point rotateCenter = calculateAveragePoint(pointsArr.points, pointsArr.countPoints);
    for (int i = 0; i < pointsArr.countPoints; ++i)
        rotatePoint(pointsArr.points[i], rotateCenter, rotateData);
    return OK;
}

err_t scalePointsArr(PointsArr &pointsArr, const ScaleData &scaleData) {
    if (pointsArr.countPoints == 0)
        return ERR_NO_DATA;
    const Point scaleCenter = calculateAveragePoint(pointsArr.points, pointsArr.countPoints);
    for (int i = 0; i < pointsArr.countPoints; ++i)
        scalePoint(pointsArr.points[i], scaleCenter, scaleData);
    return OK;
}
