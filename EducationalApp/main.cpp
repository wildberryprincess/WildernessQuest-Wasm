#include "view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartPage startScreen;
    GameModel gameModel;
    View w(startScreen, gameModel);
    startScreen.show();
    return a.exec();
}
