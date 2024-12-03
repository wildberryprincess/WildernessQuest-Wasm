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
    bool gameOver;
    QString currentCorrectAnswer = "a";
    int numQuestionsAnswered;
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
    void checkObstacleCollision();
    void checkTentCollision();

signals:
    void platformInfo(QList <QPoint> coords, QList <QPoint> sizes);
    void obstacleInfo(QList<QPoint> positions);
    void setBackground(QString filepath);
    void letterInfo(QList <QPoint> letterCoords, QStringList letters);
    void sendPrompt(SurvivalPrompt::Prompt& survivalPrompt);
    void createTent();

};
#endif // GAMEMODEL_H
