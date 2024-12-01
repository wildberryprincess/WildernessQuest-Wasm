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

    QList <QPoint> questionOneLetterCoords;

    QStringList letters;

    SurvivalPrompt allPrompts;


    void instantiateBackgrounds();
    void setPlatformCoords();
    void setLetterPositions();
    void generateLetters(QList<QPoint> letterCoords, QStringList letters);
    void randomizeSurvivalPrompts();
    void emitPromptsForLevel(int level);
    ~GameModel();


public slots:
    void setLevel(int level);

signals:
    void platformInfo(QList <QPoint> coords, QList <QPoint> sizes);
    void setBackground(QString filepath);
    void letterInfo(QList <QPoint> letterCoords, QStringList letters);
    void sendPrompt(SurvivalPrompt::Prompt& survivalPrompt);

};
#endif // GAMEMODEL_H
