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
    lives = 3; //reset lives each level
    emit livesUpdated(lives);
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
        emit removeOldLetterBodies();
        break;
    case 2:
        emit platformInfo(levelTwoPlatformCoords, levelTwoPlatformSizes);
        emit obstacleInfo(levelTwoObstaclePosition);
        emit letterInfo(questionTwoLetterCoords, letters);
        emit createTent();
        emit removeOldPlatformBodies();
        emit removeOldLetterBodies();
        break;
    case 3:
        emit removeOldPlatformBodies();
        emit platformInfo(levelThreePlatformCoords, levelThreePlatformSizes);
        emit obstacleInfo(levelThreeObstaclePosition);
        emit letterInfo(questionThreeLetterCoords, letters);
        emit createTent();
        emit removeOldLetterBodies();
        break;
    case 4:
        emit removeOldPlatformBodies();
        emit platformInfo(levelFourPlatformCoords, levelFourPlatformSizes); //TESTING TO PUSH
        emit obstacleInfo(levelFourObstaclePosition);
        emit letterInfo(questionFourLetterCoords, letters);
        emit createTent();
        emit removeOldLetterBodies();
        break;
    default:
        qWarning() << "Invalid level number:" << level; // END GAME HERE!!!! TO DO!!!
        return;
    }
    // Emit a prompt for the current level
    emitPromptsForLevel(level);
    emit sendGameInfo(currentLevel);
    qDebug() << "sendGameInfo just executed.";
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

//switched one and four
void GameModel::setLetterPositions(){
    letters = { "a", "b", "c", "d"};
    //top one is level one letter coords
    questionFourLetterCoords = { QPoint(385, 475), QPoint(575, 275), QPoint(1055, 275), QPoint(1305, 450) };
    questionTwoLetterCoords = { QPoint(1350, 260), QPoint(500, 255), QPoint(250, 105), QPoint(650, 658) };
    questionThreeLetterCoords = { QPoint(550, 50), QPoint(100, 600), QPoint(1350, 550), QPoint(750, 650) };
    questionOneLetterCoords = { QPoint(225, 100), QPoint(675, 100), QPoint(150, 700), QPoint(1350, 550) };
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

    // QPixmap levelFourBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(":/Images/background_level4.PNG");
}

//Adjust the coords for all the levels and for the letters and obstacles
void GameModel::setPlatformCoords(){
    //switched level three and level one
    levelFourPlatformCoords =  { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}, {-15, 870}};
    levelFourPlatformSizes = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}, {1450, 50}};

    levelTwoPlatformCoords =  { {10, 375}, {200, 150}, {450, 300}, {700, 375}, {400, 500}, {1150, 300}, {850, 600}, {1000, 450}, {600, 700}, {300, 800}, {-15, 870}};
    levelTwoPlatformSizes = { {300, 50}, {150, 50}, {150, 50}, {150, 50}, {300, 50}, {300, 50}, {150, 50}, {150, 50}, {150, 50}, {150, 50}, {1450, 50}};

    levelThreePlatformCoords =  { {10, 375}, {250, 250}, {475, 100}, {450, 400}, {75, 650}, {600, 500}, {700, 700}, {900, 450}, {1200, 375}, {1300, 600}, {-15, 870}};
    levelThreePlatformSizes = {     {300, 50}, {150, 50}, {200, 50}, {150, 50}, {400, 50}, {150, 50}, {150, 50}, {300, 50}, {150, 50}, {200, 50}, {1450, 50}};

    levelOnePlatformCoords =  { {10, 375}, {200, 150}, {425, 275}, {575, 150}, {300, 575}, {100, 750}, {700, 600}, {900, 600}, {1050, 450}, {1300, 600}, {-15, 870}};
    levelOnePlatformSizes = {     {300, 50}, {100, 50}, {100, 50}, {150, 50}, {300, 50}, {150, 50}, {100, 50}, {100, 50}, {200, 50}, {150, 50}, {1450, 50}};
}

//Switched levels one and four
void GameModel::setObstaclePositions() {
    levelFourObstaclePosition = { {900, 570}, {300, 645}};
    levelTwoObstaclePosition = { {425, 450}, {750, 320}, {1250, 250} };
    levelThreeObstaclePosition = { {200, 600}, {400, 600}, {1050, 400} };
    levelOneObstaclePosition = { {1200, 400}, {500, 525}, {580, 100} };
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
        emit updateProgressBar(numQuestionsAnswered);
        qDebug() << "Number of correctly answered questions: " << numQuestionsAnswered;

        // Check if the user answered enough questions to stop updates
        if (numQuestionsAnswered >= 1) {
            allQuestionsAnswered = true;
            emit proceedToNextLevel();
            qDebug() << "All questions answered for current level.";
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
     // Check if user has answered enough questions to stop updating
        if (numQuestionsAnswered >= numQuestionsPerLevel) {
        qDebug() << "No further prompts; user has answered the required questions.";
        return;
    }

    // Remove the answered question from the current prompts
    QVector<SurvivalPrompt::Prompt>* prompts = nullptr;

    switch (currentLevel) {
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
        qWarning() << "Invalid level number:" << currentLevel;
        return;
    }

    if (prompts && !prompts->isEmpty()) {
        prompts->pop_front(); // Remove the answered prompt
    }

    // Emit the next prompt or stop updating if no prompts are left
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
    emit livesUpdated(lives);
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
        if(currentLevel == 4){
            allQuestionsAnswered = false; // Reset for the next level
            numQuestionsAnswered = 0;
            win = true;
            emit gameOver(win);
        } else {
            qDebug() << "Advancing to the next level.";
            currentLevel++;
            allQuestionsAnswered = false; // Reset for the next level
            numQuestionsAnswered = 0;    // Reset the question counter
            emit resetProgressBar();
            setLevel(currentLevel);
        }
    } else {
        qDebug() << "Cannot advance: not all questions answered.";
    }
}




