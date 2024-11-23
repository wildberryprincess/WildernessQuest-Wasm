#include "gameworld.h"
#include "maincharacter.h"
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <cstdlib>

GameWorld::GameWorld(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 10.0f)), timer(this)
{
    mainPlayer = new mainCharacter(QPoint(100,100), &world);

    for (int i = 0; i < 10; i++) {
        // Platform platform(QPoint(0 + (i * 150), 200));
        Platform platform(QPoint(rand() % 1300, rand() % 800));
        platformsList.append(platform);
    }
    // Platform platform(QPoint(0, 0));
    // platformsList.append(platform);


    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 20.0f);
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    // Define the ground box shape.
    b2PolygonShape groundBox;
    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);
    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Set up the timer for the game loop
    connect(&timer, &QTimer::timeout, this, &GameWorld::updateWorld);
    timer.start(10);
}
void GameWorld::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // Fill the entire widget with the desired background color
    painter.fillRect(rect(), Qt::green); // Replace Qt::black with your desired color

    // Draw the platforms
    for (Platform platform : platformsList) {
        painter.drawImage(platform.getBoundingRect().topLeft(), platform.getImage());
    }

    // Draw the main player
    painter.drawImage(mainPlayer->getBoundingRect().topLeft(), mainPlayer->getImage());
}
void GameWorld::updateWorld() {
    // Update the main character's movement
    mainPlayer->update();

    // Step the physics world
    world.Step(1.0f / 60.0f, 6, 2);

    // Trigger a repaint
    update();
}

void GameWorld::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Inside game model key press event";
    mainPlayer->keyPressEvent(event); // Forward event to the main player
}

void GameWorld::keyReleaseEvent(QKeyEvent *event) {
    qDebug() << "Inside game model key press released event";
    mainPlayer->keyReleaseEvent(event); // Forward event to the main player
}
