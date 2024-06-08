#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>

class Door: public QObject {
    Q_OBJECT;

public:
    Door();
    ~Door() = default;

public slots:
    void openingSlot();

private:
    enum DoorStatus {
        OPEN,
        OPENING,
        CLOSED,
        CLOSING
    };

    DoorStatus status;

    QTimer openingTimer;
    QTimer closingTimer;
    QTimer openedTimer;

private slots:
    void openedSlot();
    void closingSlot();
    void closedSlot();

signals:
    void closedSignal();
};

#endif // DOOR_H
