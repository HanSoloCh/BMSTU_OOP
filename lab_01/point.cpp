#include "point.h"

#include <cstdio>

#include "error_codes.h"

enum moveDirection {
    TO = -1,
    FROM = 1,
};

err_t readPoint(Point &point, FILE *f) {
    err_t rc = OK;
    if (fscanf(f, "%lf %lf %lf", &point.x, &point.y, &point.z) != 3)
        rc = ERR_IO;
    return rc;
}

void writePoint(const Point &point, FILE *f) {
    fprintf(f, "%lf %lf %lf\n", point.x, point.y, point.z);
}

void movePoint(Point &point, const MoveData &moveData) {
    point.x += moveData.dx;
    point.y += moveData.dy;
    point.z += moveData.dz;
}

static void moveRelativeRotationCenter(Point &point, const Point &rotateCenter, moveDirection direction) {
    MoveData moveData = {
        .dx = rotateCenter.x * direction,
        .dy = rotateCenter.y * direction,
        .dz = rotateCenter.z * direction,
    };
    movePoint(point, moveData);
}

static void xRotate(Point &point, double angle) {
    double radianAngle = qDegreesToRadians(angle);
    double cosAng = cos(radianAngle);
    double sinAng = sin(radianAngle);

    double yTmp = point.y;
    double zTmp = point.z;

    point.y = yTmp * cosAng - zTmp * sinAng;
    point.z = yTmp * sinAng + zTmp * cosAng;
}

static void yRotate(Point &point, double angle) {
    double radianAngle = qDegreesToRadians(angle);
    double cosAng = cos(radianAngle);
    double sinAng = sin(radianAngle);

    double xTmp = point.x;
    double zTmp = point.z;

    point.x = xTmp * cosAng + zTmp * sinAng;
    point.z = -xTmp * sinAng + zTmp * cosAng;
}

static void zRotate(Point &point, double angle) {
    double radianAngle = qDegreesToRadians(angle);
    double cosAng = cos(radianAngle);
    double sinAng = sin(radianAngle);

    double xTmp = point.x;
    double yTmp = point.y;

    point.x = xTmp * cosAng - yTmp * sinAng;
    point.y = xTmp * sinAng + yTmp * cosAng;
}

void rotatePoint(Point &point, const Point &rotateCenter, const RotateData &rotateData) {
    moveRelativeRotationCenter(point, rotateCenter, TO);
    xRotate(point, rotateData.ox);
    yRotate(point, rotateData.oy);
    zRotate(point, rotateData.oz);
    moveRelativeRotationCenter(point, rotateCenter, FROM);
}

static void scaleCoordinates(Point &point, const ScaleData &scaleData) {
    point.x *= scaleData.kx;
    point.y *= scaleData.ky;
    point.z *= scaleData.kz;
}

void scalePoint(Point &point, const Point &scaleCenter, const ScaleData &scaleData) {
    moveRelativeRotationCenter(point, scaleCenter, TO);
    scaleCoordinates(point, scaleData);
    moveRelativeRotationCenter(point, scaleCenter, FROM);
}
