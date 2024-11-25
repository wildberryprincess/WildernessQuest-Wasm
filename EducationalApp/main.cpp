#include "view.h"
#include "survivalprompt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //TODO:: add the Prompts file into our resources file to create a survival prompt object
    //SurvivalPrompt(Prompts.json);
    QApplication a(argc, argv);
    View w;
    w.show();
    return a.exec();
}
