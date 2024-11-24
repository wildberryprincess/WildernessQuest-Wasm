#include "view.h"
#include "survivalprompt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    SurvivalPrompt("C:\\Users\\emili\\UofU\\cs3505\\docker-cs3505\\Assignments\\A9\\a9-edu-app-f24-hiphopgirlygirlz\\EducationalApp\\testQuestions.json");
    QApplication a(argc, argv);
    View w;
    w.show();
    return a.exec();
}
