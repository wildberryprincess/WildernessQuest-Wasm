#include "gamemodel.h"



GameModel::GameModel(){

    allPrompts.deserializePrompts(":/Prompts/Prompts.json");

    //initial game logisitcs
    currentLevel = 1;
    lives = 3;
    gameOver = false;

    InstantiateBackgrounds();
    SetPlateformCoords();
    }


void GameModel:: SetLevel(){
    if(currentLevel == 1){
        emit platformInfo(levelOnePlatformCoords, levelOnePlatformSizes);
        emit setBackground(backgroundImages.at(currentLevel-1));
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


void GameModel:: InstantiateBackgrounds(){

    //Adding all the background images into vector
    QPixmap levelOneBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(levelOneBG);

    QPixmap levelTwoBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(levelTwoBG);

    QPixmap levelThreeBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(levelThreeBG);

    QPixmap levelFourBG(":/Images/background_level1.PNG");
    backgroundImages.push_back(levelFourBG);
}


void GameModel:: SetPlateformCoords(){

    levelOnePlatformCoords =  { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}};
    levelOnePlatformSizes = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}};

    levelTwoPlatformCoords =  { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}};
    levelTwoPlatformSizes = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}};

    levelThreePlatformCoords =  { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}};
    levelThreePlatformSizes = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}};

    levelFourPlatformCoords =  { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}};
    levelFourPlatformSizes = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}};
}


