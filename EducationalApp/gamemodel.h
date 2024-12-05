#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QWidget>
#include "survivalprompt.h"
using std::vector;

class GameModel: public QObject {
    Q_OBJECT

public:
    explicit GameModel();
    ~GameModel();

private:
    int currentLevel;
    int lives;
    int levelProgress;
    bool win;
    QString currentCorrectAnswer = "a";
    int numQuestionsPerLevel = 1;
    int numQuestionsAnswered;
    bool allQuestionsAnswered;
    vector <QString> backgroundImages;

    QList<QPoint> levelOnePlatformCoords;
    QList<QPoint> levelOnePlatformSizes;
    QList<QPoint> levelOneObstaclePosition;

    QList<QPoint> levelTwoPlatformCoords;
    QList<QPoint> levelTwoPlatformSizes;
    QList<QPoint> levelTwoObstaclePosition;

    QList<QPoint> levelThreePlatformCoords;
    QList<QPoint> levelThreePlatformSizes;
    QList<QPoint> levelThreeObstaclePosition;

    QList<QPoint> levelFourPlatformCoords;
    QList<QPoint> levelFourPlatformSizes;
    QList<QPoint> levelFourObstaclePosition;

    QList<QPoint> questionOneLetterCoords;
    QList<QPoint> questionTwoLetterCoords;
    QList<QPoint> questionThreeLetterCoords;
    QList<QPoint> questionFourLetterCoords;


    QStringList letters;

    SurvivalPrompt allPrompts;


    void instantiateBackgrounds();
    void setPlatformCoords();
    void setObstaclePositions();
    void setLetterPositions();
    void generateLetters(QList<QPoint> letterCoords, QStringList letters);
    void randomizeSurvivalPrompts();
    void emitPromptsForLevel(int level);
    void updatePrompts();


public slots:
    void setLevel(int level);
    void checkCollidedLetter(QString letter);
    void checkObstacleCollision(QPoint obstaclePosition);
    void checkTentCollision();

signals:
    void platformInfo(QList <QPoint> coords, QList <QPoint> sizes);
    void obstacleInfo(QList<QPoint> positions);
    void setBackground(QString filepath);
    void letterInfo(QList <QPoint> letterCoords, QStringList letters);
    void sendPrompt(SurvivalPrompt::Prompt& survivalPrompt);
    void createTent();
    void incorrectCollidedLetter();
    void correctCollidedLetter();
    void proceedToNextLevel();
    void sendGameInfo(int level);
    void livesUpdated(int lives);
    void gameOver(bool win);
    void removeOldPlatformBodies();
    void removeOldLetterBodies();
};
#endif // GAMEMODEL_H
