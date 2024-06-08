#include "button.h"
#include <QDebug>

Button::Button(QWidget *parent): QPushButton(parent) {
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(pressedSlot()));
    QObject::connect(this, SIGNAL(unpressedSignal()), this, SLOT(unpressedSlot()));

    status = NOT_ACTIVE;

    setStyleSheet(
        "background-color: grey;"
        "border-style: outset;"
        "border-width: 2px;"
        "border-radius: 10px;"
        "border-color: beige;"
        "font: bold 14px;"
        "padding: 6px;"
        );
}

void Button::setFloor(size_t floor) {
    floorNum = floor;
}

void Button::pressedSlot() {
    if (status == NOT_ACTIVE) {
        this->setStyleSheet(
            "background-color: red;"
            "border-style: outset;"
            "border-width: 2px;"
            "border-radius: 10px;"
            "border-color: beige;"
            "font: bold 14px;"
            "padding: 6px;"
            );
        this->update();
        status = ACTIVE;
        this->setDisabled(true);
        emit pressedSignal(floorNum);
    }
}

void Button::unpressedSlot()
{
    if (status == ACTIVE)
    {
        setStyleSheet(
            "background-color: grey;"
            "border-style: outset;"
            "border-width: 2px;"
            "border-radius: 10px;"
            "border-color: beige;"
            "font: bold 14px;"
            "padding: 6px;"
            );
        this->update();

        status = NOT_ACTIVE;
        this->setDisabled(false);
    }
}
