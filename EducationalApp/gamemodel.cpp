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
    gameOver = false;

    instantiateBackgrounds();
    setPlatformCoords();
    setLetterPositions();
    }

GameModel::~GameModel() {

    }

void GameModel:: setLevel(int level){
    currentLevel = level;

    // Emit platform and background info
    QString bgPath = backgroundImages.at(currentLevel - 1);
    emit setBackground(bgPath);

    switch (currentLevel) {
    case 1:
        emit platformInfo(levelOnePlatformCoords, levelOnePlatformSizes);
        emit letterInfo(questionOneLetterCoords, letters);
        break;
    case 2:
        emit platformInfo(levelTwoPlatformCoords, levelTwoPlatformSizes);
        break;
    case 3:
        emit platformInfo(levelThreePlatformCoords, levelThreePlatformSizes);
        break;
    case 4:
        emit platformInfo(levelFourPlatformCoords, levelFourPlatformSizes);
        break;
    default:
        qWarning() << "Invalid level number:" << level;
        return;
    }
    // Emit a prompt for the current level
    emitPromptsForLevel(level);
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
    questionOneLetterCoords = { QPoint(850, 575), QPoint(1300, 450), QPoint(550, 270), QPoint(300,650) };

    //DO THE SAME FOR OTHER Questions
}


void GameModel:: instantiateBackgrounds(){

    //Adding all the background images into vector
    //TODO: maybe remove pixmap obj
    QPixmap levelOneBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(":/Images/background_level2.PNG"); //TESTING LEVEL 2 PHOTO PUT BACK IN LEVEL 1 LATER

    QPixmap levelTwoBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(":/Images/background_level2.PNG");

    QPixmap levelThreeBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(":/Images/background_level1.PNG");

    QPixmap levelFourBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(":/Images/background_level1.PNG");
}


void GameModel:: setPlatformCoords(){

    levelOnePlatformCoords =  { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}};
    levelOnePlatformSizes = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}};

    levelTwoPlatformCoords =  { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}};
    levelTwoPlatformSizes = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}};

    levelThreePlatformCoords =  { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}};
    levelThreePlatformSizes = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}};

    levelFourPlatformCoords =  { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}};
    levelFourPlatformSizes = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}};
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


