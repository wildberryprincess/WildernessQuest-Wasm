#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QWidget>
#include "platform.h"
#include "maincharacter.h"
#include "survivalprompt.h"
using std::vector;

class GameModel: public QObject {
    Q_OBJECT

public:
    explicit GameModel();

private:
    int currentLevel;
    int lives;
    int levelProgress;
    bool gameOver;
    vector <QPixmap> backgroundImages;
    QList <QPoint> levelOnePlatformCoords;
    QList <QPoint> levelTwoPlatformCoords;
    QList <QPoint> levelThreePlatformCoords;
    QList <QPoint> levelFourPlatformCoords;
    SurvivalPrompt allPrompts;

};
#endif // GAMEMODEL_H
