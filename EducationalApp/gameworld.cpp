#include "gameworld.h"
#include "maincharacter.h"
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <cstdlib>
#define SCALE 30.0f

GameWorld::GameWorld(QWidget *parent)
    : QWidget(parent),
    world(b2Vec2(0.0f, 10.0f)),
    timer(this)
{
    // Ensure GameWorld has focus to handle key events
    setFocusPolicy(Qt::StrongFocus);

    // Create the platform grid
    createPlatformGrid();

    // Define the ground body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 30.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 0.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    initializePlayerPosition();

    world.SetContactListener(&contactListener); // Sets the collision detection
    contactListener.setPlayerBody(mainPlayer->getBody());

    // Set up the timer for the game loop
    connect(&timer, &QTimer::timeout, this, &GameWorld::updateWorld);
    timer.start(10);
}

void GameWorld::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // Fill the entire widget with the desired background color
    QPixmap backgroundPixmap(":/Images/trial_background.png");
    painter.drawPixmap(QRect(0, 0, this->width(), this->height()), backgroundPixmap);

    // Draw the platforms
    for (Platform platform : platformsList) {
        painter.drawImage(platform.getBoundingRect().topLeft(), platform.getImage());
    }

    // Draw the main player
    painter.drawImage(mainPlayer->getBoundingRect().topLeft(), mainPlayer->getImage());
}
void GameWorld::updateWorld() {

    // Step the physics world
    world.Step(1.0f / 60.0f, 6, 2);

    // Update the main character's movement
    mainPlayer->update();

    // Trigger a repaint
    update();
}

void GameWorld::keyPressEvent(QKeyEvent *event) {
    mainPlayer->keyPressEvent(event); // Forward event to the main player
}

void GameWorld::keyReleaseEvent(QKeyEvent *event) {
    mainPlayer->keyReleaseEvent(event); // Forward event to the main player
}

GameWorld::~GameWorld() {
    platformsList.clear();
    delete mainPlayer;
}

void GameWorld::generatePlatforms() {
    // for (int i = 0; i < 10; i++) {
    //     // Platform platform(QPoint(0 + (i * 150), 200));
    //     Platform platform(QPoint(rand() % 1450, rand() % 780));
    //     platformsList.append(platform);
    // }

    QList<QPoint> positionList = { {10, 275}, {330, 425}, {800, 525}, {550, 700}, {500, 225}, {1000, 225}, {200, 600}, {1100, 700}, {1250, 400}, {675, 350}};
    QList<QPoint> sizeList = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}};

    for (int i = 0; i < 10; i++) {
        Platform platform(QPoint(positionList[i].x(), positionList[i].y()));
        platform.changeImageDimensions(sizeList[i].x(), sizeList[i].y());
        platformsList.append(platform);
    }
}

void GameWorld::createPlatformGrid() {
    // Define grid dimensions
    const int gridWidth = 1400;
    const int gridHeight = 1000;
    const int cellWidth = 100;// Handles width between each platform so logs dont overlap
    const int cellHeight = 140;  // Increase height of each grid cell for more spacing
    const int numCols = gridWidth / cellWidth;
    const int numRows = gridHeight / cellHeight;

    // Clear any existing platforms (if necessary)
    platformsList.clear();

    // Place platforms in a grid
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            // Add randomness to platform placement
            if (arc4random() % 2 == 0) continue;
                int x = col * cellWidth;
                int y = row * cellHeight;

                // // Add the platform to the QList
                generatePlatforms();

                // Create a static body in the Box2D world
                b2BodyDef platformBodyDef;
                platformBodyDef.type = b2_staticBody;
                platformBodyDef.position.Set(x / SCALE, y / SCALE);

                b2Body* platformBody = world.CreateBody(&platformBodyDef);

                // Define the shape for the platform
                b2PolygonShape platformShape;
                float platformWidth = 52.0f; // DONT CHANGE THESE they determine the collision detection width and height for the platforms
                float platformHeight = 10.0f;
                platformShape.SetAsBox(platformWidth / (2 * SCALE), platformHeight / (2 * SCALE));

                // Define the fixture for the platform with low friction
                b2FixtureDef platformFixtureDef;
                platformFixtureDef.shape = &platformShape;
                platformFixtureDef.density = 0.0f;
                platformFixtureDef.friction = 0.1f;
                platformBody->CreateFixture(&platformFixtureDef);
        }
    }
}



void GameWorld::initializePlayerPosition() {

    QPoint playerPosition(0,0); // Adjust to start above a platform
    mainPlayer = new mainCharacter(playerPosition, &world, &contactListener);
}

