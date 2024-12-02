#include "view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartPage startScreen;
    View w(startScreen);
    startScreen.show();
    return a.exec();
}
