#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "shape_processing.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    void keyPressEventWithCtrl(QKeyEvent *event, Drawer &drawer);
    void keyPressEventWithoutCtrl(QKeyEvent *event, Drawer &drawer);
    void paintEvent(QPaintEvent *event) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMenu menu;
    QGraphicsScene *scene;
    QGraphicsView *view;


    void initializeScene();
    void destroyScene();
    void setupMenu();
    void openFile();
    void saveFile();
    void saveFileAs();
};
#endif // MAINWINDOW_H
