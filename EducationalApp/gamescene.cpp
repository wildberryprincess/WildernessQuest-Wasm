#include "GameScene.h"
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <Box2D/Box2D.h>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
{
    // Box2D world setup with gravity
    b2Vec2 gravity(0.0f, 10.0f); // Gravity pointing down
    m_world = new b2World(gravity);

    // Create the hero and platforms
    createHero();
    createPlatform(50, 400, 200, 20); // Example platform
    createPlatform(300, 300, 150, 20);
    createPlatform(200, 200, 100, 20);

    // Timer for updating the scene
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GameScene::update);
    m_timer->start(1000 / 60); // 60 FPS
}

GameScene::~GameScene()
{
    delete m_world;
}

void GameScene::createHero()
{
    // Define the hero's body
    b2BodyDef heroDef;
    heroDef.type = b2_dynamicBody;
    heroDef.position.Set(100.0f / 30.0f, 100.0f / 30.0f); // Convert to meters
    m_heroBody = m_world->CreateBody(&heroDef);

    // Define the shape (a box for the hero)
    b2PolygonShape heroShape;
    heroShape.SetAsBox(15.0f / 30.0f, 30.0f / 30.0f); // Width and height

    // Define the fixture
    b2FixtureDef heroFixture;
    heroFixture.shape = &heroShape;
    heroFixture.density = 1.0f;
    heroFixture.friction = 0.3f;

    m_heroBody->CreateFixture(&heroFixture);

    // Add to the scene for visualization
    QGraphicsRectItem *heroItem = new QGraphicsRectItem(0, 0, 30, 60);
    heroItem->setBrush(Qt::blue);
    heroItem->setPos(100, 100);
    addItem(heroItem);
}

void GameScene::createPlatform(float x, float y, float width, float height)
{
    // Define the platform body
    b2BodyDef platformDef;
    platformDef.position.Set(x / 30.0f, y / 30.0f); // Convert to meters
    b2Body *platformBody = m_world->CreateBody(&platformDef);

    // Define the shape
    b2PolygonShape platformShape;
    platformShape.SetAsBox(width / 30.0f / 2, height / 30.0f / 2); // Half-width, half-height

    // Create the fixture
    platformBody->CreateFixture(&platformShape, 0.0f); // Static objects have 0 density
    m_platforms.push_back(platformBody);

    // Add to the scene for visualization
    QGraphicsRectItem *platformItem = new QGraphicsRectItem(0, 0, width, height);
    platformItem->setBrush(Qt::gray);
    platformItem->setPos(x, y);
    addItem(platformItem);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        m_leftMove = true;
        break;
    case Qt::Key_Right:
        m_rightMove = true;
        break;
    case Qt::Key_Up:
        if (m_heroBody->GetLinearVelocity().y == 0) { // Check if on ground
            b2Vec2 jumpForce(0.0f, -5.0f); // Apply upward force
            m_heroBody->ApplyLinearImpulse(jumpForce, m_heroBody->GetWorldCenter(), true);
        }
        break;
    }
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        m_leftMove = false;
        break;
    case Qt::Key_Right:
        m_rightMove = false;
        break;
    }
}

void GameScene::update()
{
    // Step the physics world
    m_world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

    // Control horizontal movement
    b2Vec2 velocity = m_heroBody->GetLinearVelocity();
    if (m_leftMove) {
        velocity.x = -5.0f; // Move left
    } else if (m_rightMove) {
        velocity.x = 5.0f; // Move right
    } else {
        velocity.x = 0.0f; // Stop horizontal movement
    }
    m_heroBody->SetLinearVelocity(velocity);

    // Update hero's position in the scene
    b2Vec2 position = m_heroBody->GetPosition();
    QGraphicsRectItem *heroItem = static_cast<QGraphicsRectItem *>(items().at(0));
    heroItem->setPos(position.x * 30.0f - 15, position.y * 30.0f - 30); // Convert to pixels
}
