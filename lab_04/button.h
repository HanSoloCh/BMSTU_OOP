#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QObject>

class Button: public QPushButton {
    Q_OBJECT;

    friend class Controller;

public:
    enum ButtonStatus {
        ACTIVE,
        NOT_ACTIVE,
    };

    explicit Button(QWidget *parent = nullptr);
    ~Button() = default;

    void setFloor(size_t floor);

public slots:
    void pressedSlot();

signals:
    void pressedSignal(size_t floor);
    void unpressedSignal();

private:
    ButtonStatus status;
    size_t floorNum;

private slots:
    void unpressedSlot();

};

#endif // BUTTON_H
