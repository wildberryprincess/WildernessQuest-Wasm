/*
Authors: Andry Joseph (andry-joseph), Emilie Parra (emilie-parra), Eliza Kitchens (wildberryprincess) & Alexis Brown (alexb000)
Assignment #9: Educational Game
Reviewer: Eliza Kitchens (.cpp &.h)

This class creates a gameModel object which stores the game data and handles game logic.
*/
#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QWidget>
#include "survivalprompt.h"
using std::vector;


class GameModel: public QObject {
    Q_OBJECT

public:
    /**
     * @brief GameModel: Constructor
     * @param parent : Inherits from QWidget
     */
    explicit GameModel();

    ~GameModel();

private:
    int currentLevel;
    int lives;
    int levelProgress;
    bool win;
    QString currentCorrectAnswer = "a";
    int numQuestionsPerLevel = 5;
    int numQuestionsAnswered;
    bool allQuestionsAnswered;
    vector <QString> backgroundImages;
    QStringList letters;
    SurvivalPrompt allPrompts;

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

    /**
     * @brief instantiateBackgrounds: method adds each background png to a vector in the order that they appear in the game.
     */
    void instantiateBackgrounds();

    /**
     * @brief setPlatformCoords: method manually assigns platform coordinates according to the background image and the level difficulty.
     */
    void setPlatformCoords();

    /**
     * @brief setObstaclePositions: method manually assigns bear (obstacle) coordinates according to the platform placement and the level difficulty.
     */
    void setObstaclePositions();

    /**
     * @brief setLetterPositions: method manually assigns letter coordinates according to the platform placement and the level difficulty.
     */
    void setLetterPositions();

    /**
     * @brief randomizeSurvivalPrompts: method shuffles each of the Prompt vectors so that a prompts are displayed in a random order each game.
     */
    void randomizeSurvivalPrompts();

    /**
     * @brief emitPromptsForLevel: method emits the first of the list of prompts for the corresponding game level and stores the correct
     * answer to the multiple choice prompt in the gameModel object.
     * @param level: the game level (1-4)
     */
    void emitPromptsForLevel(int level);

    /**
     * @brief updatePrompts: method emits prompts when the user answers previous prompts correctly. Each time a prompt is sent, it is removed
     * from the list of prompts to prevent duplicate prompts from being displayed.
     */
    void updatePrompts();


public slots:

    /**
     * @brief setLevel: method emits all game info needed for each level including background, platforms, obstacles, letters, lives, prompts
     * tent. This method also clears the 2D Bodies from previous levels.
     * @param level
     */
    void setLevel(int level);

    /**
     * @brief checkCollidedLetter: method checks if the letter that the player collided with is the correct or incorrect answer to the prompt
     * then, emits a signal to display feedback to the player.
     * @param letter: the letter that the user collided with.
     */
    void checkCollidedLetter(QString letter);

    /**
     * @brief checkObstacleCollision: method decrement's players lives and sends signal to update lives display upon collision with a bear (obstacle),
     * removes the obstacle from the view and deletes the obstacle 2D body to prevent futher collisions with that particular obstacle.
     * @param obstaclePosition: coordinates of the obstacle
     */
    void checkObstacleCollision(QPoint obstaclePosition);

    /**
     * @brief checkTentCollision: upon player collision with the tent, method checks if all questions have been answered for that level.
     * If all questions are complete, the game will advance to the next level. If player is on level 4, then the player wins and the game is over.
     */
    void checkTentCollision();


signals:

    /**
     * @brief platformInfo: sends platform screen coordinates and sizes to the gameWorld for display.
     * @param coords: screen coordinates for each platform
     * @param sizes: size of platform
     */
    void platformInfo(QList <QPoint> coords, QList <QPoint> sizes);

    /**
     * @brief obstacleInfo: sends bear (obstacle) screen coordinates to the gameWorld for display.
     * @param positions: screen coordinates of the obstacles
     */
    void obstacleInfo(QList<QPoint> positions);

    /**
     * @brief setBackground: sends the background image filepath to gameWorld for display.
     * @param filepath: location of the background image
     */
    void setBackground(QString filepath);

    /**
     * @brief letterInfo: sends the letter screen coordinates and a list of letters to gameWorld for display.
     * @param letterCoords: screen coordinates of the letter objects
     * @param letters: letters representing multiple choice answers
     */
    void letterInfo(QList <QPoint> letterCoords, QStringList letters);

    /**
     * @brief sendPrompt: sends a single prompt to gameWorld for display.
     * @param survivalPrompt: a prompt object
     */
    void sendPrompt(SurvivalPrompt::Prompt& survivalPrompt);

    /**
     * @brief createTent: sends signal to gameWorld to display the tent object.
     */
    void createTent();

    /**
     * @brief incorrectCollidedLetter: sends signal to gameWorld to display that the answer was incorrect.
     */
    void incorrectCollidedLetter();

    /**
     * @brief correctCollidedLetter: sends signal to gameWorld to display that the answer was correct.
     */
    void correctCollidedLetter();

    /**
     * @brief proceedToNextLevel: sends signal to gameWorld to display that all of the prompts for that level have been answered
     * and that the player should run to the tent to proceed to the next level.
     */
    void proceedToNextLevel();

    /**
     * @brief sendGameInfo: sends signal to gameWorld to display the game title and current level.
     * @param level: current level
     */
    void sendGameInfo(int level);

    /**
     * @brief livesUpdated: sends signal to gameWorld to display hearts corresponding to the player's lives.
     * @param lives: how many lives the player has
     */
    void livesUpdated(int lives);

    /**
     * @brief gameOver: sends signal to gameWorld to display either lose or win game over screen.
     * @param win: did the player win or loose
     */
    void gameOver(bool win);

    /**
     * @brief removeOldPlatformBodies: sends signal to gameWorld to stop displaying platforms.
     */
    void removeOldPlatformBodies();

    /**
     * @brief removeOldLetterBodies: sends signal to gameWorld to stop displaying letters.
     */
    void removeOldLetterBodies();

    /**
     * @brief updateProgressBar: sends signal to gameWorld to display the player's progress answering the level prompts.
     * @param numOfQuestionsAnswered: the number of questions that the player has answered
     */
    void updateProgressBar(int numOfQuestionsAnswered);

    /**
     * @brief removeOldObstacleBodies: sends signal to gameWorld to stop displaying bears (obstacles).
     */
    void removeOldObstacleBodies();

    /**
     * @brief resetProgressBar: sends signal to gameWorld to reset progress bar between levels
     */
    void resetProgressBar();
};
#endif // GAMEMODEL_H
