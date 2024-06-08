#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setFixedSize(290, 500);
    this->setWindowTitle("Lab_04");
    layout = std::unique_ptr<QVBoxLayout>(new QVBoxLayout);
    this->ui->centralwidget->setLayout(layout.get());
    layout->addWidget(elevator.widget());
}

MainWindow::~MainWindow() {
    delete ui;
}

