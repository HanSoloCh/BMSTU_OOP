#include "controller.h"

Controller::Controller(QWidget *parent) : QWidget(parent) {
    layout = std::unique_ptr<QVBoxLayout>(new QVBoxLayout);
    this->setLayout(layout.get());

    QObject::connect(this, SIGNAL(floorPassedSignal(size_t,Direction)), this, SLOT(floorPassedSlot(size_t,Direction)));
    QObject::connect(this, SIGNAL(controllerStoppedSignal()), this, SLOT(controllerStoppedSlot()));

    status = FREE;
    currentFloor = 1;
    direction = STOP;

    for (int i = 0; i < floorMaxCount; ++i)     {
        std::shared_ptr<Button> btn(new Button);
        btn->setFloor(floorMaxCount - i);
        btn->setText(QString::number(floorMaxCount - i));

        buttons.insert(buttons.begin(), btn);
        layout->addWidget(btn.get());

        visitedFloors.push_back(true);

        QObject::connect(btn.get(), SIGNAL(pressedSignal(size_t)), this, SLOT(newTargetSlot(size_t)));
    }
}

void Controller::newTargetSlot(size_t floor) {
    visitedFloors[floor - 1] = false;

    if (status != HAS_TARGET) {
        status = HAS_TARGET;
        hasTarget(floor);
        targetFloor = floor;

        if (currentFloor == targetFloor)
            emit floorPassedSignal(currentFloor, direction);
        else {
            direction = targetFloor > currentFloor ? UP : DOWN;
            emit getTargetSignal(targetFloor, currentFloor);
        }
    }
}

void Controller::controllerStoppedSlot() {
    if (status == BUSY) {
        status = FREE;
        emit cabinStoppedSignal(true, currentFloor);
    }
}

void Controller::floorPassedSlot(size_t floor, Direction direct) {
    if (status == HAS_TARGET || status == BUSY) {
        status = BUSY;
        currentFloor = floor;
        direction = direct;

        if (currentFloor == targetFloor) {
            buttons[floor - 1]->unpressedSlot();
            visitedFloors[floor - 1] = true;

            if (hasTarget(targetFloor))
                emit cabinStoppedSignal(false, currentFloor, targetFloor);
            else
                emit controllerStoppedSignal();
        }
    }
}

bool Controller::hasTarget(size_t &newFloor) {
    Direction direct;
    if (direction != STOP)
        direct = direction;
    else
        direct = DOWN;

    // Сначала просматриваем этажи по направлению движения
    for (size_t i = currentFloor - 1; i >= 0 && i < floorMaxCount; i += direct) {
        if (!visitedFloors[i]) {
            newFloor = i + 1;
            return true;
        }
    }

    // Затем против направления движения
    for (size_t i = currentFloor - 1; i >= 0 && i < floorMaxCount; i -= direct) {
        if (!visitedFloors[i]) {
            newFloor = i + 1;
            return true;
        }
    }

    return false;
}
