/*
Authors: Andry Joseph (andry-joseph), Emilie Parra (emilie-parra), Eliza Kitchens (wildberryprincess) & Alexis Brown (alexb000)
Assignment #9: Educational Game
Reviewer: Alexis Brown (.cpp &.h)


GameWorld is where all of the visual aspects of the game are stored. When an action in the world takes place, GameWorld sends a signal
to the respective slot in model through the View. GameWorld handles displaying the platforms, obstacles, letter, background, and main character.
It also handles displaying all of the text on the screen. When a collision is detected in gamecontactlistener, the GameWorld sends a signal to
the model, where the logic of storing game information exists.
*/

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <Box2D/Box2D.h>
#include <QWidget>
#include <QString>
#include <QTimer>
#include <QLabel>
#include <QProgressBar>
#include <functional> // For std::function
#include <map>
#include "platform.h"
#include <queue>
#include "letterobjects.h"
#include "obstacle.h"
#include "gamecontactlistener.h" // Include here to use GameContactListener
#include "maincharacter.h"
#include "tent.h"
#include "heart.h"
#include "bodydata.h"
#include "gamemodel.h"

class GameWorld : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief GameWorld: Constructor
     * @param parent : Inherits from QWidget
     */
    explicit GameWorld(QWidget *parent = nullptr);

    /**
     * @brief checkLetter: When a user collides with a letter, GameWorld emits a signal inside this method to GameModel
     * @param letter : The letter that has been collided with "A," "B," "C," "D"
     */
    void checkLetter(QString letter);

    /**
     * @brief handleObstacleCollisions: When a user collides with an obstacle, GameWorld emits a signal in this method to GameModel
     * @param collidedObstacle: The obstacle that was collided with
     */
    void handleObstacleCollisions(Obstacle collidedObstacle);

protected:
    /**
     * @brief paintEvent: Updates the game world and UI
     * @param event: update();
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief keyPressEvent: Handles when the user presses a key and notifies MainCharacter class
     * @param event: User pressed key
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief keyReleaseEvent: Handles when the user releases a key and notifies MainCharacter class
     * @param event: User released key
     */
    void keyReleaseEvent(QKeyEvent *event) override;

public slots:
    /**
     * @brief updateWorld: When a new level begins, the world is reset back to its original settings
     */
    void updateWorld();

    /**
     * @brief generatePlatforms: Creates the platformList based off of the positions passed in from the model
     * This slot acitvates each time a new level beings.
     * @param coords: Coordinates of the platforms
     * @param sizes: Sizes of the platforms
     */
    void generatePlatforms(QList<QPoint> coords, QList<QPoint> sizes);

    /**
     * @brief generateObstacles: Creates the obstacles (bears) to be placed on the screen based off of the positions emited in model
     * This slot activates each time a new level begins
     * @param positionList: The coordinates of the obstacles
     */
    void generateObstacles(QList<QPoint> positionList);

    /**
     * @brief setBackgroundPixMap: Resets the background for the game based off of the level the user is on
     * @param filepath: The location of the image to be reset
     */
    void setBackgroundPixMap(QString filepath);

    /**
     * @brief generateLetters: Creates the letter's to be displayed on the screen, based off of the emited coordinates
     * as well as the name of the letter, "A", "B", "C", "D." This slot is called when the user moves on to a new level
     * @param coords: The coordinates of the letters to be placed on the screen
     * @param letters: The name of the letter
     */
    void generateLetters(QList<QPoint> coords, QStringList letters);

    /**
     * @brief generateTent: creates the tent object that the user has to reach to move on the new level.
     * This slot is called each time a new level begins
     */
    void generateTent();

    /**
     * @brief displayPrompt: Displays the question at the top of the screen. Model sends the prompt to GameWorld
     * @param prompt: The question
     */
    void displayPrompt(SurvivalPrompt::Prompt& prompt);

    /**
     * @brief handleTentCollisions: When the user collides with the tent, the ContactListener notifies the game world.
     * The Game World then emits a signal to the model to handle the logic.
     */
    void handleTentCollisions();

    /**
     * @brief setCharacterType: Sets the character based on the user's selection of character in the start screen
     * @param type: An Integer 0 = "GirlScout", 1 = "BoyScout", 2 = "Non-Binary Character"
     */
    void setCharacterType(int type);

    /**
     * @brief handleIncorrectCollidedLetter: When the user collides with the incorect letter, a prompt is displayed
     * to let the user know that they need to try again
     */
    void handleIncorrectCollidedLetter();

    /**
     * @brief handleCorrectCollidedLetter: When the user collides with the correct letter, a prompt is displayed
     * to let the user know that they collided with the correct letter
     */
    void handleCorrectCollidedLetter();

    /**
     * @brief handleProceedToNextLevel: When the user answers all of the required number of questions, a prompt
     * is displayed to let the user know that they need to go to the tent to move on to the next level
     */
    void handleProceedToNextLevel();

    /**
     * @brief displayGameInfo: Displays the title of the game and the level the user is on
     * @param level: The level the user is currently playing
     */
    void displayGameInfo(int level);

    /**
     * @brief updateLivesDisplay: When the user loses a life from hitting an obstacle, the lives that are displayed on the screen are updated
     * @param lives: The number of lives the user currently has
     */
    void updateLivesDisplay(int lives);

    /**
     * @brief removeExistingPlatforms: Removes the existing platform bodies from the screen, so that there are no issues with "ghost" collisions
     * This happens at the beginning of each level
     */
    void removeExistingPlatforms();

    /**
     * @brief removeExistingLetters: Removes the existing letter bodies from the screen, so that there are no issues with "ghost" letters
     * This happens at the beginning of each level
     */
    void removeExistingLetters();

    /**
     * @brief changeProgressBar: Changes the progress bar based on the number of correctly answered questions
     * @param numOfQuestions: Number of questions that have been answered
     */
    void changeProgressBar(int numOfQuestions);

    /**
     * @brief setProgressBarToZero: Resets the progress bar back to zero when a new level begins
     */
    void setProgressBarToZero();

    /**
     * @brief removeExistingObstacles: Removes the bears from previous levels to clear up the screen for new level.
     */
    void removeExistingObstacles();

private:
    b2World world;
    QTimer timer;
    QPixmap* currentBackground;
    int currentLives = 3;
    QList<Heart> heartsList;
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
    QLabel* gameInfoLabel; //display level and lives
    QProgressBar* progressBar;
    QLabel* progressLabel;
    int numOfQuestionsLeft;
    QString progressText;
    QVector<std::pair<QPoint, b2Body*>> obstacleBodies;
    QVector<std::pair<QPoint, b2Body*>> platformBodies;
    QVector<std::pair<QPoint, b2Body*>> letterBodies;
    std::queue<std::function<void()>> deferredActions;

    ~GameWorld();

    /**
     * @brief createPlatformGrid: Creates the platform bodies to be displayed on the screen based off of
     * the positions for each level
     */
    void createPlatformGrid();

    /**
     * @brief initializePlayerPosition: Initializes the intial position of where the player stars for each level
     */
    void initializePlayerPosition();

    /**
     * @brief initializeHearts: Initializes the hearts to be displayed on the screen for each level
     */
    void initializeHearts();

signals:
    /**
     * @brief checkLetterInModel: When a user collides with a letter, model is notified of the specific letter to then
     * check and see if the user answered the question correctly
     * @param letter: The letter the user collided with
     */
    void checkLetterInModel(QString letter);

    /**
     * @brief collidedWithObstacle: When a user collides with an obstacle (a bear), the model is notified of the specifc
     * coordinate of the obstacle which will then be removed from the screen
     * @param collidedObstaclePosition: The coordinate of the collided obstacle
     */
    void collidedWithObstacle(QPoint collidedObstaclePosition);

    /**
     * @brief collidedWithTent: When the user collides with the tent, the model is notified so that the levels can be changed
     */
    void collidedWithTent();
};

#endif // GAMEWORLD_H
