#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QWidget>
#include <QTimer>
#include <QList>
#include <QLabel>
#include <Box2D/Box2D.h>
#include "gamemodel.h"
#include "platform.h"
#include "obstacle.h"
#include "maincharacter.h"
#include "gamecontactlistener.h"
#include "letterobjects.h"

class GameWorld : public QWidget {
    Q_OBJECT

public:
    explicit GameWorld(QWidget *parent = nullptr);
    void setGameModel(GameModel& model);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public slots:
    void updateWorld();
    void generatePlatforms(QList<QPoint> coords, QList<QPoint> sizes);
    void generateObstacles();
    void setBackgroundPixMap(QString filepath);
    void generateLetters(QList<QPoint> coords, QStringList letters);
    void displayPrompt(SurvivalPrompt::Prompt& prompt);

private:
    GameModel *gameModel = nullptr; // Add GameModel pointer
    b2World world;
    QTimer timer;
    QPixmap* currentBackground;
    QList<Platform> platformsList;
    QList<Obstacle> obstaclesList;
    mainCharacter* mainPlayer;
    GameContactListener contactListener;
    QList<LetterObjects> letterObjectsList;
    SurvivalPrompt survivalPrompts;
    vector<SurvivalPrompt>::iterator currentPrompt; //iterator for current question
    QLabel* promptLabel; //display for the question

    ~GameWorld();



    void createPlatformGrid();

    void initializePlayerPosition();
};

#endif // GAMEWORLD_H
