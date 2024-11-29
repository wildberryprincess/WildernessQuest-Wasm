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
    vector <QString> backgroundImages;

    QList <QPoint> levelOnePlatformCoords;
    QList <QPoint> levelOnePlatformSizes;

    QList <QPoint> levelTwoPlatformCoords;
    QList <QPoint> levelTwoPlatformSizes;

    QList <QPoint> levelThreePlatformCoords;
    QList <QPoint> levelThreePlatformSizes;

    QList <QPoint> levelFourPlatformCoords;
    QList <QPoint> levelFourPlatformSizes;

    SurvivalPrompt allPrompts;


    void InstantiateBackgrounds();
    void SetPlateformCoords();
    ~GameModel();


public slots:
    void SetLevel(int level);

signals:
    void platformInfo(QList <QPoint> coords, QList <QPoint> sizes);
    void setBackground(QString filepath);

};
#endif // GAMEMODEL_H
