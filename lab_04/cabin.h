#ifndef CABIN_H
#define CABIN_H

#include <QObject>

#include "door.h"
#include "controller.h"

class Cabin: public QObject {
    Q_OBJECT;

public:
    enum CabinStatus {
        STANDING,
        STARTING,
        MOVING
    };

    explicit Cabin(QObject *parent = nullptr);
    ~Cabin() = default;

public slots:
    void startingSlot(size_t targetFloor, size_t currentFloor);
    void stoppedSlot(bool isLast, size_t currentFloor, size_t targetFloor);

private:
    void saveState(size_t targetFloor, size_t currentFloor);
    Door door;
    size_t currentFloor;
    size_t targetFloor;
    Direction direction;
    CabinStatus status;
    bool hasTarget;

    QTimer moveTimer;

private slots:
    void moveSlot();

signals:
    void floorPassedSignal(size_t floor, Direction dir);
    void openDoorsSignal();
    void movingSignal();
};

#endif // CABIN_H
