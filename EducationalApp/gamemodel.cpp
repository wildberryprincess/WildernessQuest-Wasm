#include "gamemodel.h"



 GameModel::GameModel(){
    currentLevel = 0;
    lives = 3;
     allPrompts.deserializePrompts(":/Prompts/Prompts.json");
    }


