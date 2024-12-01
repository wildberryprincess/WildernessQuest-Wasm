#include "view.h"
#include "ui_view.h"
#include "gamemodel.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
    , gameWorld(new GameWorld(this))  // Initialize a single GameWorld instance
{
    ui->setupUi(this);

    // Initialize GameModel
    GameModel *gameModel = new GameModel();


    // Connect setUpModel signal in View to setLevel slot in GameModel
    connect(this, &View::setUpModel, gameModel, &GameModel::setLevel);
    // Connect GameModel's platformInfo signal to GameWorld's generatePlatforms slot
    connect(gameModel, &GameModel::platformInfo, gameWorld, &GameWorld::generatePlatforms);

    connect(gameModel, &GameModel::obstacleInfo, gameWorld, &GameWorld::generateObstacles);

    connect(gameModel, &GameModel::setBackground, gameWorld, &GameWorld::setBackgroundPixMap);

    connect(gameModel, &GameModel::letterInfo, gameWorld, &GameWorld::generateLetters);

    connect(gameModel, &GameModel::sendPrompt, gameWorld, &GameWorld::displayPrompt);

    setUpInitialGameModel(); // Example call to initialize model

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
