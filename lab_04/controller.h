#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>

#include <vector>
#include <memory>

#include "button.h"

const int floorMaxCount = 10;
const int doorsTime = 600;
const int movingTime = 1000;

enum Direction {
    DOWN = -1,
    STOP = 0,
    UP = 1
};


class Controller: public QWidget {
    Q_OBJECT;

public:
    enum ControllerStatus {
        FREE,
        HAS_TARGET,
        BUSY
    };

    explicit Controller(QWidget *parent = nullptr);
    ~Controller() = default;

public slots:
    void newTargetSlot(size_t floor);
    void floorPassedSlot(size_t floor, Direction direction);
    void controllerStoppedSlot();

private:
    bool hasTarget(size_t &newFloor);

    ControllerStatus status;
    Direction direction;
    size_t currentFloor;
    size_t targetFloor;

    std::vector<std::shared_ptr<Button>> buttons;
    std::vector<bool> visitedFloors;
    std::unique_ptr<QVBoxLayout> layout;

signals:
    void controllerStoppedSignal();
    void cabinStoppedSignal(bool, size_t, size_t = 1);
    void getTargetSignal(size_t targetFloor, size_t currentFloor);
    void floorPassedSignal(size_t floor, Direction direction);
};

#endif // CONTROLLER_H
