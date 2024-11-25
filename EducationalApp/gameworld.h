#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QWidget>
#include <QTimer>
#include <QList>
#include <Box2D/Box2D.h>
#include "platform.h"
#include "maincharacter.h"
#include "gamecontactlistener.h"

class GameWorld : public QWidget {
    Q_OBJECT

public:
    explicit GameWorld(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void updateWorld();

private:
    b2World world;
    QTimer timer;
    QList<Platform> platformsList;
    mainCharacter* mainPlayer;
    GameContactListener contactListener;

    ~GameWorld();

    void generatePlatforms();
    void createPlatformGrid();

    void initializePlayerPosition();
};

#endif // GAMEWORLD_H
