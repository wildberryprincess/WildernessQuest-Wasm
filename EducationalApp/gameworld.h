#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QWidget>
#include <QTimer>
#include <QList>
#include <Box2D/Box2D.h>
#include "gamemodel.h"
#include "platform.h"
#include "maincharacter.h"
#include "gamecontactlistener.h"

class GameWorld : public QWidget {
    Q_OBJECT

public:
    explicit GameWorld(QWidget *parent = nullptr);
    void setGameModel(GameModel& model);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void updateWorld();
    void generatePlatforms(QList<QPoint> coords, QList<QPoint> sizes);
    void setBackgroundPixMap(QString filepath);

private:
    b2World world;
    QTimer timer;
    QPixmap* currentBackground;
    QList<Platform> platformsList;
    mainCharacter* mainPlayer;
    GameContactListener contactListener;

    ~GameWorld();


    void createPlatformGrid();

    void initializePlayerPosition();
};

#endif // GAMEWORLD_H
