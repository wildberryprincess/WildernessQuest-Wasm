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

void GameWorld::GetInitialModelInfo() {

    //emit getPatformInfor

    // Connect signals from GameModel to slots in GameWorld
    //connect(gameModel, &GameModel::platformInfo, this, &GameWorld::generatePlatforms);
    //connect(gameModel, &GameModel::setBackground, this, &GameWorld::setBackgroundPixMap);

    // Additional connections can be added here as needed
}

void GameWorld::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // Fill the entire widget with the desired background color
    //QPixmap backgroundPixmap(":/Images/background_level1.PNG");

    //TODO:: setting a background image from the gamemodel class
    //backgroundPixmap.loadFromData();
    painter.drawPixmap(QRect(0, 0, this->width(), this->height()), *currentBackground);

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
    delete currentBackground;
}
void GameWorld::setBackgroundPixMap(QString filepath) {
    currentBackground = new QPixmap(filepath);
}

//TODO:: making this method into a slot that takes two params of the coords and the size of the platforms
void GameWorld::generatePlatforms(QList<QPoint> positionList, QList<QPoint> sizeList) {
    //QList<QPoint> positionList = { {10, 375}, {330, 525}, {800, 625}, {550, 800}, {500, 325}, {1000, 325}, {200, 700}, {1100, 800}, {1250, 500}, {675, 450}};
    //QList<QPoint> sizeList = { {300, 50}, {150, 50}, {300, 50}, {250, 50}, {200, 50}, {150, 50}, {300, 50}, {150, 50}, {150, 50}, {200, 50}};

    for (int i = 0; i < 10; i++) {
        Platform platform(QPoint(positionList[i].x(), positionList[i].y()));
        platform.changeImageDimensions(sizeList[i].x(), sizeList[i].y());
        platformsList.append(platform);
    }
}

void GameWorld::createPlatformGrid() {
    // Clear any existing platforms (if necessary)
    platformsList.clear();

    // Add the platform to the QList
    //generatePlatforms();

    for (const Platform& platform : platformsList) {

        // Calculate center of platform (This is how the collision works)
        float centerX = platform.position.x() + (platform.imageSize.x() / 2.0f);
        float centerY = platform.position.y() + (platform.imageSize.y() / 2.0f);

        // Create a static body in the Box2D world
        b2BodyDef platformBodyDef;
        platformBodyDef.type = b2_staticBody;
        platformBodyDef.position.Set(centerX / SCALE, centerY / SCALE);
        b2Body* platformBody = world.CreateBody(&platformBodyDef);

        // Define the shape for the platform
        b2PolygonShape platformShape;
        platformShape.SetAsBox(platform.imageSize.x() / (2.0f * SCALE), platform.imageSize.y() / (2.0f * SCALE));

        // Define the fixture for the platform with low friction
        b2FixtureDef platformFixtureDef;
        platformFixtureDef.shape = &platformShape;
        platformFixtureDef.density = 0.0f;
        platformFixtureDef.friction = 0.1f;
        platformBody->CreateFixture(&platformFixtureDef);
    }
}



void GameWorld::initializePlayerPosition() {
    QPoint playerPosition(100,0); // Adjust to start above a platform
    mainPlayer = new mainCharacter(playerPosition, &world, &contactListener);
}

