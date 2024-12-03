#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <Box2D/Box2D.h>
#include <QWidget>
#include <QString>
#include <QTimer>
#include <QLabel>
#include <functional> // For std::function
#include "platform.h"
#include <queue>
#include "letterobjects.h"
#include "obstacle.h"
#include "gamecontactlistener.h" // Include here to use GameContactListener
#include "maincharacter.h"
#include "tent.h"
#include "bodydata.h"
#include "gamemodel.h"

class GameWorld : public QWidget {
    Q_OBJECT

public:
    explicit GameWorld(QWidget *parent = nullptr);
    void setGameModel(GameModel& model);
    void checkLetter(QString letter);
    void handleObstacleCollisions();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public slots:
    void updateWorld();
    void generatePlatforms(QList<QPoint> coords, QList<QPoint> sizes);
    void generateObstacles(QList<QPoint> positionList);
    void setBackgroundPixMap(QString filepath);
    void generateLetters(QList<QPoint> coords, QStringList letters);
    void generateTent();
    void displayPrompt(SurvivalPrompt::Prompt& prompt);
    void handleTentCollisions();
    void setCharacterType(int type);

private:
    GameModel *gameModel = nullptr; // Add GameModel pointer
    b2World world;
    QTimer timer;
    QPixmap* currentBackground;
    QList<Platform> platformsList;
    QList<Obstacle> obstaclesList;
    mainCharacter* mainPlayer;
    Tent* levelUpTent;
    int characterType;
    GameContactListener* contactListener;
    QList<LetterObjects> letterObjectsList;
    SurvivalPrompt survivalPrompts;
    vector<SurvivalPrompt>::iterator currentPrompt; //iterator for current question
    QLabel* promptLabel; //display for the question

    std::queue<std::function<void()>> deferredActions;

    ~GameWorld();



    void createPlatformGrid();

    void initializePlayerPosition();
signals:
    void checkLetterInModel(QString letter);
    void collidedWithObstacle();
    void collidedWithTent();
};
#endif // GAMEWORLD_H
