#include "cabin.h"

#include <QDebug>

Cabin::Cabin(QObject *parent): QObject(parent) {
    status = STANDING;
    hasTarget = false;

    QObject::connect(this, SIGNAL(movingSignal()), this, SLOT(moveSlot()));
    QObject::connect(&moveTimer, SIGNAL(timeout()), this, SLOT(moveSlot()));
    QObject::connect(this, SIGNAL(openDoorsSignal()), &door, SLOT(openingSlot()));
    QObject::connect(&door, SIGNAL(closedSignal()), this, SLOT(moveSlot()));
}

void Cabin::moveSlot() {
    if (hasTarget) {
        if (status == STARTING || status == STANDING)
            status = MOVING;
        else
            currentFloor += direction;

        qDebug() << "Лифт на" << currentFloor << "этаже";

        if (currentFloor != targetFloor)
            moveTimer.start(movingTime);

        emit floorPassedSignal(currentFloor, direction);
    }
}

void Cabin::startingSlot(size_t targetFloor, size_t currentFloor) {
    if (status == STANDING) {
        status = STARTING;
        hasTarget = true;
        saveState(targetFloor, currentFloor);
        emit movingSignal();
    }
}

void Cabin::stoppedSlot(bool isLast, size_t currentFloor, size_t targetFloor) {
    if (status == MOVING || status == STARTING) {
        status = STANDING;
        saveState(targetFloor, currentFloor);
        qDebug() << "Лифт остановился на этаже: " << currentFloor;

        if (isLast)
            hasTarget= false;

        moveTimer.stop();
        emit openDoorsSignal();
    }
}

void Cabin::saveState(size_t floorNum, size_t curFloor) {
    targetFloor = floorNum;
    currentFloor = curFloor;
    if (currentFloor > targetFloor)
        direction = DOWN;
    else
        direction = UP;
}
