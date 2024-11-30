#include "gamemodel.h"



GameModel::GameModel(){

    allPrompts.deserializePrompts(":/Prompts/Prompts.json");

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
    if (currentLevel == 1) {
        QString bgPath = backgroundImages.at(currentLevel - 1);
        qDebug() << "Setting up level" << level << ". Emitting setBackground with:" << bgPath;

        emit platformInfo(levelOnePlatformCoords, levelOnePlatformSizes); // Update platforms
        emit setBackground(bgPath); // Emit background path
        emit letterInfo(questionOneLetterCoords, letters);
    }
    else if(currentLevel == 2){
        emit platformInfo(levelTwoPlatformCoords, levelTwoPlatformSizes);
        emit setBackground(backgroundImages.at(currentLevel-1));
    }
    else if(currentLevel == 3){
        emit platformInfo(levelThreePlatformCoords, levelThreePlatformSizes);
        emit setBackground(backgroundImages.at(currentLevel-1));
    }
    else if(currentLevel == 4){
        emit platformInfo(levelFourPlatformCoords, levelFourPlatformSizes);
        emit setBackground(backgroundImages.at(currentLevel-1));
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
    backgroundImages.push_back(":/Images/background_level1.PNG");

    QPixmap levelTwoBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(":/Images/background_level1.PNG");

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


