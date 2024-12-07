#include "gamemodel.h"
#include <algorithm> // For std::random_shuffle
#include <random>    // For std::mt19937
#include <ctime>     // For time()

GameModel::GameModel(){

    allPrompts.deserializePrompts(":/Prompts/Prompts.json");
    randomizeSurvivalPrompts();
    currentLevel = 1;
    lives = 3;
    win = false;
    numQuestionsAnswered = 0;
    instantiateBackgrounds();
    setPlatformCoords();
    setLetterPositions();
    setObstaclePositions();
}


GameModel::~GameModel() {
}


void GameModel:: setLevel(int level){
    currentLevel = level;
    allQuestionsAnswered = false;
    lives = 3; //reset lives each level
    emit livesUpdated(lives);
    QString bgPath = backgroundImages.at(currentLevel - 1);
    emit setBackground(bgPath);

    switch (currentLevel) {
    case 1:
        emit platformInfo(levelOnePlatformCoords, levelOnePlatformSizes);
        emit letterInfo(questionOneLetterCoords, letters);
        emit obstacleInfo(levelOneObstaclePosition);
        emit createTent();
        emit removeOldLetterBodies();
        emit removeOldObstacleBodies();
        break;
    case 2:
        emit platformInfo(levelTwoPlatformCoords, levelTwoPlatformSizes);
        emit obstacleInfo(levelTwoObstaclePosition);
        emit letterInfo(questionTwoLetterCoords, letters);
        emit createTent();
        emit removeOldPlatformBodies();
        emit removeOldLetterBodies();
        emit removeOldObstacleBodies();
        break;
    case 3:
        emit removeOldPlatformBodies();
        emit platformInfo(levelThreePlatformCoords, levelThreePlatformSizes);
        emit obstacleInfo(levelThreeObstaclePosition);
        emit letterInfo(questionThreeLetterCoords, letters);
        emit createTent();
        emit removeOldLetterBodies();
        emit removeOldObstacleBodies();
        break;
    case 4:
        emit removeOldPlatformBodies();
        emit platformInfo(levelFourPlatformCoords, levelFourPlatformSizes);
        emit obstacleInfo(levelFourObstaclePosition);
        emit letterInfo(questionFourLetterCoords, letters);
        emit createTent();
        emit removeOldLetterBodies();
        emit removeOldObstacleBodies();
        break;
    default:
        qWarning() << "Invalid level number:" << level;
        return;
    }

    // Emit a prompt for the current level
    emitPromptsForLevel(level);
    emit sendGameInfo(currentLevel);
}


void GameModel::emitPromptsForLevel(int level) {
    QVector<SurvivalPrompt::Prompt>* prompts = nullptr;
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
        currentCorrectAnswer = prompt.correctAnswer.at(0).toLower();
    } else {
        qWarning() << "No prompts available for level" << level;
    }
}


void GameModel::setLetterPositions(){
    letters = { "a", "b", "c", "d"};
    questionOneLetterCoords = { QPoint(385, 475), QPoint(575, 275), QPoint(1055, 275), QPoint(1305, 450) };
    questionTwoLetterCoords = { QPoint(1350, 260), QPoint(500, 255), QPoint(250, 105), QPoint(650, 658) };
    questionThreeLetterCoords = { QPoint(550, 50), QPoint(100, 600), QPoint(1350, 550), QPoint(750, 650) };
    questionFourLetterCoords = { QPoint(225, 100), QPoint(675, 100), QPoint(150, 700), QPoint(1350, 550) };
}


void GameModel:: instantiateBackgrounds(){

    backgroundImages.push_back(":/Images/background_level1.PNG");
    backgroundImages.push_back(":/Images/background_level2.PNG");
    backgroundImages.push_back(":/Images/background_level3.PNG");
    backgroundImages.push_back(":/Images/background_level4.PNG");
}


void GameModel::setPlatformCoords(){
    levelOnePlatformCoords =  { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}, {-15, 870}};
    levelOnePlatformSizes = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}, {1450, 50}};

    levelTwoPlatformCoords =  { {10, 375}, {200, 150}, {450, 300}, {700, 375}, {400, 500}, {1150, 300}, {850, 600}, {1000, 450}, {600, 700}, {300, 800}, {-15, 870}};
    levelTwoPlatformSizes = { {300, 50}, {150, 50}, {150, 50}, {150, 50}, {300, 50}, {300, 50}, {150, 50}, {150, 50}, {150, 50}, {150, 50}, {1450, 50}};

    levelThreePlatformCoords =  { {10, 375}, {250, 250}, {475, 100}, {450, 400}, {75, 650}, {600, 500}, {700, 700}, {900, 450}, {1200, 375}, {1225, 600}, {-15, 870}};
    levelThreePlatformSizes = {     {300, 50}, {150, 50}, {200, 50}, {150, 50}, {400, 50}, {150, 50}, {150, 50}, {300, 50}, {150, 50}, {200, 50}, {1450, 50}};

    levelFourPlatformCoords =  { {10, 375}, {200, 150}, {425, 275}, {575, 150}, {300, 575}, {100, 750}, {700, 600}, {900, 600}, {1050, 450}, {1250, 600}, {-15, 870}};
    levelFourPlatformSizes = {     {300, 50}, {100, 50}, {100, 50}, {150, 50}, {300, 50}, {150, 50}, {100, 50}, {100, 50}, {200, 50}, {150, 50}, {1450, 50}};
}


void GameModel::setObstaclePositions() {
    levelOneObstaclePosition = { {900, 570}, {300, 645}, {200, 320}};
    levelTwoObstaclePosition = { {425, 450}, {750, 320}, {1250, 250} };
    levelThreeObstaclePosition = { {200, 600}, {400, 600}, {1050, 400} };
    levelFourObstaclePosition = { {1200, 400}, {500, 525}, {580, 100} };
}


void GameModel::randomizeSurvivalPrompts(){
    unsigned seed = static_cast<unsigned>(time(nullptr));
    std::mt19937 generator(seed); // Mersenne Twister random number generator
    std::shuffle(allPrompts.levelOnePrompts.begin(), allPrompts.levelOnePrompts.end(), generator);
    std::shuffle(allPrompts.levelTwoPrompts.begin(), allPrompts.levelTwoPrompts.end(), generator);
    std::shuffle(allPrompts.levelThreePrompts.begin(), allPrompts.levelThreePrompts.end(), generator);
    std::shuffle(allPrompts.levelFourPrompts.begin(), allPrompts.levelFourPrompts.end(), generator);
}


void GameModel::checkCollidedLetter(QString letter) {
    if (letter == currentCorrectAnswer) {
        numQuestionsAnswered++;
        emit updateProgressBar(numQuestionsAnswered);

        // Check if the user answered enough questions to stop updates
        if (numQuestionsAnswered >= numQuestionsPerLevel) {
            allQuestionsAnswered = true;
            emit proceedToNextLevel();
        } else {
            updatePrompts(); // Emit the next prompt
        }
        emit correctCollidedLetter(); // Notify of correct answer collision
    } else {
        emit incorrectCollidedLetter(); // Notify of incorrect answer collision
    }
}


void GameModel::updatePrompts() {
     // Check if user has answered enough questions per level
        if (numQuestionsAnswered >= numQuestionsPerLevel) {
        return;
    }

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
        currentCorrectAnswer = nextPrompt.correctAnswer.at(0).toLower(); //update correct answer
    }
}


void GameModel::checkObstacleCollision(QPoint obstaclePosition){
    lives--;
    emit livesUpdated(lives);

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
    }
}


void GameModel::checkTentCollision() {
    if (allQuestionsAnswered) {
        if(currentLevel == 4){
            allQuestionsAnswered = false; // Reset for the next level
            numQuestionsAnswered = 0;
            win = true;
            emit gameOver(win);
        } else {
            currentLevel++; // Advance to the next level
            allQuestionsAnswered = false; // Reset for the next level
            numQuestionsAnswered = 0;    // Reset the question counter
            emit resetProgressBar();
            setLevel(currentLevel);
        }
    }
}




