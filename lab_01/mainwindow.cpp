#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QKeyEvent>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QPen>

#include "shape_processing.h"
#include "data_processing.h"
#include "error_codes.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupMenu();
    initializeScene();
    setFocus();
}

MainWindow::~MainWindow()
{
    Drawer drawer = initDrawer("white", scene);
    shapeProcessing(dataProcessing(drawer, DELETE));
    destroyScene();
    delete ui;
}

void MainWindow::setupMenu() {
    menu.setTitle("File");

    QAction *openAction = menu.addAction("Open");
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    QAction *saveAction = menu.addAction("Save");
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFileAs);

    ui->menubar->addMenu(&menu);
}

void MainWindow::initializeScene() {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);
}

void MainWindow::destroyScene() {
    delete scene;
    delete view;
}

void MainWindow::openFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open source file", "../lab_01/data", "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        QByteArray byteArray = filePath.toUtf8();
        const char *charFileName = byteArray.constData();
        Drawer drawer = initDrawer("white", scene);
        ShapeAction &shapeData = dataProcessing(drawer, INIT, charFileName);
        if (shapeProcessing(shapeData) != OK)
            QMessageBox::warning(this, "Error", "Could not load data from file.");
    } else
        QMessageBox::warning(this, "Error", "Could not open file for reading.");
}


void MainWindow::saveFileAs() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save source file", "../lab_01/data", "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        QByteArray byteArray = filePath.toUtf8();
        const char *charFileName = byteArray.constData();
        Drawer drawer = initDrawer("white", scene);
        ShapeAction &shapeData = dataProcessing(drawer, SAVE, charFileName);
        if (shapeProcessing(shapeData) != OK)
            QMessageBox::warning(this, "Error", "Could not save data to file.");
    } else
        QMessageBox::warning(this, "Error", "Could not open file for writing.");

}

void MainWindow::paintEvent(QPaintEvent *event) {
    (void)event;
    Drawer drawer = initDrawer("white", scene);
    shapeProcessing(dataProcessing(drawer, DRAW));
}


void MainWindow::keyPressEventWithoutCtrl(QKeyEvent *event, Drawer &drawer) {
    int pressedButton = event->key();
    switch (pressedButton) {
    case Qt::Key_D:
        shapeProcessing(dataProcessing(drawer, MOVE, 5.0, 0.0, 0.0));
        update();
        break;
    case Qt::Key_A:
        shapeProcessing(dataProcessing(drawer, MOVE, -5.0, 0.0, 0.0));
        update();
        break;
    case Qt::Key_W:
        shapeProcessing(dataProcessing(drawer, MOVE, 0.0, -5.0, .0));
        update();
        break;
    case Qt::Key_S:
        shapeProcessing(dataProcessing(drawer, MOVE, 0.0, 5.0, 0.0));
        update();
        break;
    }
}

void MainWindow::keyPressEventWithCtrl(QKeyEvent *event, Drawer &drawer) {
    int pressedButton = event->key();
    switch (pressedButton) {
    case Qt::Key_D:
        shapeProcessing(dataProcessing(drawer, ROTATE, 0.0, 0.0, 1.0));
        update();
        break;
    case Qt::Key_A:
        shapeProcessing(dataProcessing(drawer, ROTATE, 0.0, 0.0, -1.0));
        update();
        break;
    case Qt::Key_S:
        shapeProcessing(dataProcessing(drawer, ROTATE, 1.0, 0.0, 0.0));
        update();
        break;
    case Qt::Key_W:
        shapeProcessing(dataProcessing(drawer, ROTATE, -1.0, 0.0, 0.0));
        update();
        break;
    case Qt::Key_E:
        shapeProcessing(dataProcessing(drawer, ROTATE, 0.0, 1.0, 0.0));
        update();
        break;
    case Qt::Key_Q:
        shapeProcessing(dataProcessing(drawer, ROTATE, 0.0, -1.0, 0.0));
        update();
        break;
    case Qt::Key_Equal:
        shapeProcessing(dataProcessing(drawer, SCALE, 1.2, 1.2, 1.2));
        update();
        break;
    case Qt::Key_Minus:
        shapeProcessing(dataProcessing(drawer, SCALE, 0.8, 0.8, 0.8));
        update();
        break;
    }

}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    bool ctrlPressed = event->modifiers() & Qt::ControlModifier;
    Drawer drawer;
    if (ctrlPressed)
        keyPressEventWithCtrl(event, drawer);
    else
        keyPressEventWithoutCtrl(event, drawer);
}
