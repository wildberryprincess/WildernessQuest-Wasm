#include "gameworld.h"
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsRectItem>
GameWorld::GameWorld(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 10.0f)),
    timer(this),
    //setting the image
    image(":/images/hero.png")
{
    Platforms platform(QPoint(500, 500));
    platformsList.append(platform);
    //  // Create the hero and platforms
    // createPlatform(50, 400, 200, 20); // Example platform
    // createPlatform(300, 300, 150, 20);
    // createPlatform(200, 200, 100, 20);
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
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    heroBody = world.CreateBody(&bodyDef);
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;
    // Override the default friction.
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.9;
    // Add the shape to the body.
    heroBody->CreateFixture(&fixtureDef);
    printf("Init world\n");
    connect(&timer, &QTimer::timeout, this, &SceneWidget::updateWorld);
    timer.start(10);
}
void GameWorld::paintEvent(QPaintEvent *) {
    // Create a painter
    QPainter painter(this);
    // Fill the entire widget with the desired background color
    painter.fillRect(rect(), Qt::green); // Replace Qt::black with your desired color
    b2Vec2 position = heroBody->GetPosition();
    float angle = heroBody->GetAngle();
    //    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    painter.drawImage((int)(position.x*20), (int)(position.y*20), image);
    // painter.drawImage(200, 200, image);
    painter.drawImage(platformsList[0].getBoundingRect().topLeft(), platformsList[0].getImage());
    //    qDebug() << image;
    painter.end();
}
void GameWorld::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);
    update();
}
// void GameWorld::createPlatform(float x, float y, float width, float height)
// {
//     // Define the platform body
//     b2BodyDef platformDef;
//     platformDef.position.Set(x / 30.0f, y / 30.0f); // Convert to meters
//     b2Body *platformBody = world.CreateBody(&platformDef);
//     // Define the shape
//     b2PolygonShape platformShape;
//     platformShape.SetAsBox(width / 30.0f / 2, height / 30.0f / 2); // Half-width, half-height
//     // Create the fixture
//     platformBody->CreateFixture(&platformShape, 0.0f); // Static objects have 0 density
//     m_platforms.push_back(platformBody);
//     //TODO: Next task, figure out how to draw the platforms on the widget.
//     // Add to the scene for visualization
//     QGraphicsRectItem *platformItem = new QGraphicsRectItem(0, 0, width, height);
//     platformItem->setBrush(Qt::gray);
//     platformItem->setPos(x, y);
//     platformItem->show();
// }
