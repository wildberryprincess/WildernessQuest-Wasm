#include "view.h"
#include "view.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ui->widget->show(); // Unsure what this is

    // for (int i = 0; i < 5; i++) {
    //     int randXPosition = rand() % 700;
    //     int randYPosition = rand() % 700;
    // }

    // Platforms platform(QPoint(500, 500));
    // platformsList.append(platform);

    // update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// void MainWindow::paintEvent(QPaintEvent *event) {
//     QPainter painter(this);
//     painter.drawImage(platformsList[0].getBoundingRect().topLeft(), platformsList[0].getImage());
// }
