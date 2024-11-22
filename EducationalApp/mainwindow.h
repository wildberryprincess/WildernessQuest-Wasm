#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "platforms.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QList<Platforms> platformsList;

protected:
    // paints the platforms onto display
    void paintEvent(QPaintEvent *) override;

    //sallows the user to move the player based on keystroke
    // void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
