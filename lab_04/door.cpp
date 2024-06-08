#include "door.h"
#include "controller.h"

#include <QTimer>

Door::Door() {
    status = CLOSED;

    QObject::connect(&openingTimer, SIGNAL(timeout()), this, SLOT(openedSlot()));
    QObject::connect(&openedTimer, SIGNAL(timeout()), this, SLOT(closingSlot()));
    QObject::connect(&closingTimer, SIGNAL(timeout()), this, SLOT(closedSlot()));
}

void Door::openingSlot() {
    if (status == CLOSED || status == CLOSING) {
        qDebug() << "Двери открываются";

        if (status == CLOSED) {
            status = OPENING;
            openingTimer.start(doorsTime);
        } else {
            status = OPENING;
            auto timer = closingTimer.remainingTime();
            closingTimer.stop();
            openingTimer.start(doorsTime - timer);
        }
    }
}

void Door::openedSlot() {
    if (status == OPENING) {
        status = OPEN;
        qDebug() << "Двери открыты";
        openedTimer.start(doorsTime);
    }
}

void Door::closingSlot() {
    if (status == OPEN) {
        status = CLOSING;
        qDebug() << "Двери закрываются";
        closingTimer.start(doorsTime);
    }
}

void Door::closedSlot()
{
    if (status == CLOSING)
    {
        status = CLOSED;
        qDebug() << "Двери закрыты.";
        emit closedSignal();
    }
}
