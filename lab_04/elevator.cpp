#include <QPalette>

#include "elevator.h"

Elevator::Elevator(QObject *parent) : QObject(parent) {
    controller.setStyleSheet("background-color:green;");

    QObject::connect(&cabin, SIGNAL(floorPassedSignal(size_t,Direction)), &controller, SLOT(floorPassedSlot(size_t,Direction)));
    QObject::connect(&controller, SIGNAL(getTargetSignal(size_t,size_t)), &cabin, SLOT(startingSlot(size_t,size_t)));
    QObject::connect(&controller, SIGNAL(cabinStoppedSignal(bool,size_t,size_t)), &cabin, SLOT(stoppedSlot(bool,size_t,size_t)));
}

QWidget *Elevator::widget() {
    return &controller;
}
