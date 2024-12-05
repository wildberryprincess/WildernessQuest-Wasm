#include "view.h"
#include "ui_view.h"
#include "gamemodel.h"

View::View(StartPage& startScreen, GameModel& gameModel, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
    , startScreen(&startScreen)
    , gameWorld(new GameWorld(this))  // Initialize a single GameWorld instance
{
    ui->setupUi(this);

    // Connect setUpModel signal in View to setLevel slot in GameModel
    connect(this, &View::setUpModel, &gameModel, &GameModel::setLevel);
    // Connect GameModel's platformInfo signal to GameWorld's generatePlatforms slot
    connect(&gameModel, &GameModel::platformInfo, gameWorld, &GameWorld::generatePlatforms);

    connect(&gameModel, &GameModel::obstacleInfo, gameWorld, &GameWorld::generateObstacles);

    connect(&gameModel, &GameModel::setBackground, gameWorld, &GameWorld::setBackgroundPixMap);

    connect(&gameModel, &GameModel::sendGameInfo, gameWorld, &GameWorld::displayGameInfo);

    connect(&gameModel, &GameModel::letterInfo, gameWorld, &GameWorld::generateLetters);

    connect(&gameModel, &GameModel::sendPrompt, gameWorld, &GameWorld::displayPrompt);

    connect(&gameModel, &GameModel::livesUpdated, gameWorld, &GameWorld::updateLivesDisplay);

    connect(gameWorld, &GameWorld::checkLetterInModel, &gameModel, &GameModel::checkCollidedLetter);

    connect(&gameModel, &GameModel::incorrectCollidedLetter, gameWorld, &GameWorld::handleIncorrectCollidedLetter);

    connect(&gameModel, &GameModel::correctCollidedLetter, gameWorld, &GameWorld::handleCorrectCollidedLetter);

    connect(&gameModel, &GameModel::proceedToNextLevel, gameWorld, &GameWorld::handleProceedToNextLevel);

    connect(gameWorld, &GameWorld::collidedWithObstacle, &gameModel, &GameModel::checkObstacleCollision);

    connect(&startScreen, &StartPage::updateCharacterInfo, this, &View::displayGame);
    connect(this, &View::updateCharacter, gameWorld, &GameWorld::setCharacterType);

    connect(&gameModel,&GameModel::createTent, gameWorld, &GameWorld::generateTent);

    connect(gameWorld, &GameWorld::collidedWithTent, &gameModel, &GameModel::checkTentCollision);

    connect(&gameModel, &GameModel::gameOver, this, &View::displayEndScreen);
    connect(this, &View::showWinScreen, &startScreen, &StartPage::updateWinScreen);
    connect(this, &View::showLoseScreen, &startScreen, &StartPage::updateLoseScreen);

    connect(&gameModel, &GameModel::removeOldPlatformBodies, gameWorld, &GameWorld::removeExistingPlatforms);
    connect(&gameModel, &GameModel::removeOldLetterBodies, gameWorld, &GameWorld::removeExistingLetters);

    connect(&gameModel, &GameModel::updateProgressBar, gameWorld, &GameWorld::changeProgressBar);
    connect(&gameModel, &GameModel::resetProgressBar, gameWorld, &GameWorld::setProgressBarToZero);

    connect(&gameModel, &GameModel::removeOldObstacleBodies, gameWorld, &GameWorld::removeExistingObstacles);

    setUpInitialGameModel(); // Call to Initialize model

    // Add gameWorld as the central widget for the View
    setCentralWidget(gameWorld);  // Ensures only this instance is displayed and updated
}

void View::setUpInitialGameModel() {
    emit setUpModel(1); // Emit signal with level 1
}

View::~View()
{
    delete ui;
}

void View::displayGame(int characterType) {
    this->show();
    emit updateCharacter(characterType);
    qDebug() << "Inside displayGame: " << characterType;
}

void View::displayEndScreen(bool win) {
    this->hide();

    if (win) {
        qDebug() << "Hides Screen! Win";
        emit showWinScreen();
    } else {
        qDebug() << "Hides Screen! Lose";
        emit showLoseScreen();
    }
}
