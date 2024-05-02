#include "shape_draw.h"

#include <QGraphicsScene>

#include "shape.h"
#include "edge_arr.h"
#include "point_arr.h"

static err_t drawEdgeArr(Drawer &drawer, const EdgesArr &edgesArr, const PointsArr &pointsArr);
static err_t drawEdge(Drawer &drawer, const Edge &edge, const PointsArr &pointsArr);
static void drawLine(Drawer &drawer, const Point &point1, const Point &point2);

static void cleanScene(Drawer &drawer);

static QPointF projectPoint(const Point &point);


err_t drawShape(const Shape &shape, Drawer &drawer) {
    if (!isShapeRead(shape))
        return ERR_NO_DATA;

    cleanScene(drawer);
    return drawEdgeArr(drawer, shape.edgesArr, shape.pointsArr);
}

static err_t drawEdgeArr(Drawer &drawer, const EdgesArr &edgesArr, const PointsArr &pointsArr) {
    err_t rc = OK;
    for (int i = 0; rc == OK && i < edgesArr.countEdges; ++i)
        rc = drawEdge(drawer, edgesArr.edge[i], pointsArr);
    return rc;
}

static err_t drawEdge(Drawer &drawer, const Edge &edge, const PointsArr &pointsArr) {
    if (!checkEdgeIndex(edge, pointsArr.countPoints))
        return ERR_RANGE;
    drawLine(drawer, pointsArr.points[edge.from], pointsArr.points[edge.to]);
    return OK;
}

static void drawLine(Drawer &drawer, const Point &point1, const Point &point2) {
    QPointF projectPoint1 = projectPoint(point1);
    QPointF projectPoint2 = projectPoint(point2);
    drawer.scene->addLine(projectPoint1.x(), projectPoint1.y(), projectPoint2.x(), projectPoint2.y(), drawer.pen);
}

static QPointF projectPoint(const Point &point) {
    double x = point.x;
    double y = point.y;
    return QPointF(x, y);
}

static void cleanScene(Drawer &drawer) {
    drawer.scene->clear();
}
