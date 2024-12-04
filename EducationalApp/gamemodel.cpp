#include "gamemodel.h"
#include <algorithm> // For std::random_shuffle
#include <random>    // For std::mt19937
#include <ctime>     // For time()



GameModel::GameModel(){

    allPrompts.deserializePrompts(":/Prompts/Prompts.json");
    randomizeSurvivalPrompts();
    //initial game logisitcs
    currentLevel = 1;
    lives = 3;
    win = false;
    numQuestionsAnswered = 0;

    instantiateBackgrounds();
    setPlatformCoords();
    setLetterPositions();
    setObstaclePositions();
    qDebug() << "GameModel constructor obstacle count: " << levelOneObstaclePosition.size();
}

GameModel::~GameModel() {
}

void GameModel:: setLevel(int level){
    currentLevel = level;
    allQuestionsAnswered = false;
    // Emit platform and background info
    QString bgPath = backgroundImages.at(currentLevel - 1);
    emit setBackground(bgPath);

    switch (currentLevel) {
    case 1:
        emit platformInfo(levelOnePlatformCoords, levelOnePlatformSizes);
        emit letterInfo(questionOneLetterCoords, letters);

        qDebug() << "Inside setLevel obstacle count: " << levelOneObstaclePosition.size();
        emit obstacleInfo(levelOneObstaclePosition);
        emit createTent();
        break;
    case 2:
        emit platformInfo(levelTwoPlatformCoords, levelTwoPlatformSizes);
        emit obstacleInfo(levelTwoObstaclePosition);
        emit createTent();
        break;
    case 3:
        emit platformInfo(levelThreePlatformCoords, levelThreePlatformSizes);
        emit obstacleInfo(levelThreeObstaclePosition);
        emit createTent();
        break;
    case 4:
        emit platformInfo(levelFourPlatformCoords, levelFourPlatformSizes); //TESTING TO PUSH
        emit obstacleInfo(levelFourObstaclePosition);
        emit createTent();
        break;
    default:
        qWarning() << "Invalid level number:" << level; // END GAME HERE!!!! TO DO!!!
        return;
    }
    // Emit a prompt for the current level
    emitPromptsForLevel(level);
    emit sendGameInfo(currentLevel);
}

// emits only one prompt at a time, so we can emit the next one in response to a correct answer in the future
void GameModel::emitPromptsForLevel(int level) {
    QVector<SurvivalPrompt::Prompt>* prompts = nullptr;

    // Map level to the corresponding prompts vector
    switch (level) {
    case 1:
        prompts = &allPrompts.levelOnePrompts;
        break;
    case 2:
        prompts = &allPrompts.levelTwoPrompts;
        break;
    case 3:
        prompts = &allPrompts.levelThreePrompts;
        break;
    case 4:
        prompts = &allPrompts.levelFourPrompts;
        break;
    default:
        qWarning() << "Invalid level number:" << level;
        return;
    }

    // Emit only the first prompt if available
    if (prompts && !prompts->isEmpty()) {
        auto& prompt = prompts->front();
        emit sendPrompt(prompt);
        currentCorrectAnswer = prompt.correctAnswer.at(0).toLower(); //SET CORRECT ANSWER HERE
    } else {
        qWarning() << "No prompts available for level" << level;
    }
}

void GameModel::setLetterPositions(){
    letters = { "a", "b", "c", "d"};
    questionTwoLetterCoords = { QPoint(385, 475), QPoint(575, 275), QPoint(1055, 275), QPoint(1305, 450) };
    questionOneLetterCoords = { QPoint(1300, 260), QPoint(500, 255), QPoint(250, 105), QPoint(650, 658) };


    //DO THE SAME FOR OTHER Questions
}


void GameModel:: instantiateBackgrounds(){

    //Adding all the background images into vector
    //TODO: maybe remove pixmap obj
    //QPixmap levelOneBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(":/Images/background_level1.PNG"); //TESTING LEVEL 3 PHOTO PUT BACK IN LEVEL 1 LATERR

    //QPixmap levelTwoBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(":/Images/background_level2.PNG");

    //QPixmap levelThreeBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(":/Images/background_level3.PNG");

    //QPixmap levelFourBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(":/Images/background_level1.PNG");
}

//Adjust the coords for all the levels and for the letters and obstacles
void GameModel::setPlatformCoords(){
    //switched level one and level two
    levelTwoPlatformCoords =  { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}};
    levelTwoPlatformSizes = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}};

    levelOnePlatformCoords =  { {10, 375}, {200, 150}, {450, 300}, {700, 375}, {400, 500}, {1150, 300}, {700, 600}, {900, 450}, {600, 700}, {300, 800}};
    levelOnePlatformSizes = {    {300, 50}, {150, 50}, {150, 50}, {150, 50}, {300, 50}, {300, 50}, {150, 50}, {150, 50}, {150, 50}, {150, 50}};

    levelThreePlatformCoords =  { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}};
    levelThreePlatformSizes = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}};

    levelFourPlatformCoords =  { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}};
    levelFourPlatformSizes = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}};
}

//Switched levels one and two
void GameModel::setObstaclePositions() {
    levelTwoObstaclePosition = { {900, 570}, {300, 645}};
    levelOneObstaclePosition = { {425, 450}, {750, 320}, {1170, 250} };
    levelThreeObstaclePosition = { {100, 100}, {200, 200}, {300, 300} };
    levelFourObstaclePosition = { {100, 100}, {200, 200}, {300, 300} };
}

void GameModel::randomizeSurvivalPrompts(){
    unsigned seed = static_cast<unsigned>(time(nullptr));
    std::mt19937 generator(seed); // Mersenne Twister random number generator

    // Shuffle the prompts for each level
    std::shuffle(allPrompts.levelOnePrompts.begin(), allPrompts.levelOnePrompts.end(), generator);
    std::shuffle(allPrompts.levelTwoPrompts.begin(), allPrompts.levelTwoPrompts.end(), generator);
    std::shuffle(allPrompts.levelThreePrompts.begin(), allPrompts.levelThreePrompts.end(), generator);
    std::shuffle(allPrompts.levelFourPrompts.begin(), allPrompts.levelFourPrompts.end(), generator);
}

void GameModel::checkCollidedLetter(QString letter) {
    // Check for correct answer
    if (letter == currentCorrectAnswer) {
        qDebug() << "The user selected the correct answer: " << letter;

        numQuestionsAnswered++; // Increment the correct answer count
        qDebug() << "Number of correctly answered questions: " << numQuestionsAnswered;
        // Check if the user answered enough questions to advance
        if (numQuestionsAnswered >= 2) {
            allQuestionsAnswered = true;
            numQuestionsAnswered = 0; // Reset question counter for the new level
        } else {
            updatePrompts(); // Emit the next prompt
        }
        emit correctCollidedLetter(); // Notify of correct answer collision
    } else {
        qDebug() << "The user collided with an incorrect letter. User letter: "
                 << letter << " Correct letter: " << currentCorrectAnswer;
        emit incorrectCollidedLetter(); // Notify of incorrect answer collision
    }
}


void GameModel::updatePrompts() {
    // Remove the answered question from the current prompts
    QVector<SurvivalPrompt::Prompt>* prompts = nullptr;

    switch (currentLevel) {
    case 1:
        prompts = &allPrompts.levelOnePrompts;
        break;
    case 2:
        prompts = &allPrompts.levelTwoPrompts;
        break;
    case 3: //TEST TEST
        prompts = &allPrompts.levelThreePrompts;
        break;
    case 4:
        prompts = &allPrompts.levelFourPrompts;
        break;
    default:
        qWarning() << "Invalid level number:" << currentLevel;
        return;
    }

    if (prompts && !prompts->isEmpty()) {
        prompts->pop_front(); // Remove the answered prompt
    }

    // Emit the next prompt or level up if no prompts are left
    if (prompts && !prompts->isEmpty()) {
        auto& nextPrompt = prompts->front();
        emit sendPrompt(nextPrompt);
        currentCorrectAnswer = nextPrompt.correctAnswer.at(0).toLower();
    } else {
        qDebug() << "All questions answered for level " << currentLevel;
    }
}


void GameModel::checkObstacleCollision(QPoint obstaclePosition){
    qDebug() << "Inside model, the user collided with a bear";
    lives--;
    qDebug() << "Lives left: " << lives;

    if (currentLevel == 1) {
        levelOneObstaclePosition.removeAll(obstaclePosition);
    } else if (currentLevel == 3) {
        levelTwoObstaclePosition.removeAll(obstaclePosition);
    } else if (currentLevel == 2) {
        levelThreeObstaclePosition.removeAll(obstaclePosition);
    } else if (currentLevel == 4) {
        levelFourObstaclePosition.removeAll(obstaclePosition);
    }

    if (lives == 0) {
        emit gameOver(win);
        qDebug() << "Game Over! There are 0 Lives!";
    }
}

void GameModel::checkTentCollision() {
    qDebug() << "Inside model, the user has collided with a tent";
    if (allQuestionsAnswered) {
        qDebug() << "Advancing to the next level.";
        currentLevel++;
        allQuestionsAnswered = false; // Reset for the next level
        numQuestionsAnswered = 0;    // Reset the question counter
        setLevel(currentLevel);
    } else {
        qDebug() << "Cannot advance: not all questions answered.";
    }

    // Somewhere in the collision check, once all questions in level 4 are answered correctly, and tent is collided with, then send emit gameOver(win);
    // win = true;
    // emit gameOver(win);
}




