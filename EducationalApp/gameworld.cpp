#include "gameworld.h"
#include "maincharacter.h"
#include "obstacle.h"
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <cstdlib>
#include <bodydata.h>
#define SCALE 30.0f


GameWorld::GameWorld(QWidget *parent)
    : QWidget(parent),
    world(b2Vec2(0.0f, 10.0f)),
    timer(this),
    currentBackground(nullptr),
    promptLabel(new QLabel(this)),
    contactListener(new GameContactListener())
{

    // Ensure GameWorld has focus to handle key events
    setFocusPolicy(Qt::StrongFocus);
    characterType = 0;

    // Define the ground body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 30.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 0.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    initializePlayerPosition();
    levelUpTent = new Tent();

    world.SetContactListener(contactListener); // Sets the collision detection

    contactListener->setGameWorld(this);

    // Set up the prompt display
    promptLabel->setWordWrap(true);
    promptLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);
    promptLabel->setStyleSheet("font-size: 14px; color: black; font-family: Courier;");
    promptLabel->setGeometry(725, 10, 700, 150);

    // Set up the timer for the game loop
    connect(&timer, &QTimer::timeout, this, &GameWorld::updateWorld);
    timer.start(10);
}


void GameWorld::paintEvent(QPaintEvent *) {

    QPainter painter(this);

    if (currentBackground) {
        if (!currentBackground->isNull()) {
            painter.drawPixmap(QRect(0, 0, this->width(), this->height()), *currentBackground);
        } else {
            qWarning() << "currentBackground is null.";
            painter.fillRect(this->rect(), Qt::black);
        }
    } else {
        qWarning() << "currentBackground is not initialized.";
        painter.fillRect(this->rect(), Qt::black);
    }

    // Draw the platforms
    for (Platform platform : platformsList) {
        painter.drawImage(platform.getBoundingRect().topLeft(), platform.getImage());
    }

    // Draw the obstacle
    for (Obstacle obstacle : obstaclesList) {
        painter.drawImage(obstacle.getBoundingRect().topLeft(), obstacle.getImage());
    }

    // Draw the letters
    for (LetterObjects letter : letterObjectsList) {
        painter.drawImage(letter.getBoundingRect().topLeft(), letter.getImage());
    }
    // Draw Tent
    painter.drawImage(levelUpTent->getBoundingRect().topLeft(), levelUpTent->getImage());


    // Draw the main player
    painter.drawImage(mainPlayer->getBoundingRect().topLeft(), mainPlayer->getImage());
}

void GameWorld::updateWorld() {

    // Step the physics world
    world.Step(1.0f / 60.0f, 6, 2);

    // Update the main character's movement
    mainPlayer->update();


    if (!contactListener->collidedLetter.isEmpty()) {
        qDebug() << "Player collided with letter:" << contactListener->collidedLetter;
        // Process the collision, e.g., remove the letter or update the game state
        contactListener->collidedLetter.clear(); // Reset after processing
    }

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
    letterObjectsList.clear();
    obstaclesList.clear();

    delete contactListener;
    delete mainPlayer;
    delete currentBackground;
}

void GameWorld::setCharacterType(int type) {
    characterType = type;
    qDebug() << "Inside setCharacterType: " << characterType;

    initializePlayerPosition();
}
void GameWorld::setBackgroundPixMap(QString filepath) {

    if (currentBackground) {
        delete currentBackground;
        currentBackground = nullptr;
    }

    currentBackground = new QPixmap(filepath);

    update(); // This triggers a repaint
}

void GameWorld::generatePlatforms(QList<QPoint> positionList, QList<QPoint> sizeList) {
    for (int i = 0; i < positionList.size(); i++) {
        Platform platform(QPoint(positionList[i].x(), positionList[i].y()));
        platform.changeImageDimensions(sizeList[i].x(), sizeList[i].y());
        platformsList.append(platform);
    }
    createPlatformGrid();
}

void GameWorld::generateObstacles(QList<QPoint> positionList) {

    qDebug() << "Obstacle list size: " << positionList.size();

    for (int i = 0; i < positionList.size(); ++i) {
        // Create the obstacle
        Obstacle obstacle(positionList[i]);
        obstaclesList.append(obstacle);

        // Create a static body in the Box2D world
        b2BodyDef obstacleBodyDef;
        obstacleBodyDef.type = b2_staticBody;
        obstacleBodyDef.position.Set(positionList[i].x() / SCALE, positionList[i].y() / SCALE);
        b2Body* obstacleBody = world.CreateBody(&obstacleBodyDef);

        // Define the shape for the obstacle
        b2PolygonShape obstacleShape;
        obstacleShape.SetAsBox(3.0f / SCALE, 3.0f / SCALE); // Adjust size as needed

        // Define the fixture for the obstacle
        b2FixtureDef obstacleFixtureDef;
        obstacleFixtureDef.shape = &obstacleShape;
        obstacleFixtureDef.isSensor = true; // Mark this fixture as a sensor
        obstacleBody->CreateFixture(&obstacleFixtureDef);

        // Attach user data for collision handling
        BodyData* obstacleData = new BodyData("obstacle", new Obstacle(obstacle));
        obstacleBody->SetUserData(obstacleData);

        qDebug() << "Obstacle created with UserData:" << obstacleBody;
    }
}

void GameWorld::createPlatformGrid() {

    for (Platform& platform : platformsList) {

        // Calculate center of platform (This is how the collision works)
        float centerX = platform.position.x() + (platform.imageSize.x() / 2.0f);
        float centerY = platform.position.y() + (platform.imageSize.y() / 2.0f);

        // Create a static body in the Box2D world
        b2BodyDef platformBodyDef;
        platformBodyDef.type = b2_staticBody;
        platformBodyDef.position.Set(centerX / SCALE, centerY / SCALE);
        b2Body* platformBody = world.CreateBody(&platformBodyDef);
        BodyData* platformData = new BodyData("platform", new Platform(platform)); // Allocate dynamically
        platformBody->SetUserData(platformData);
        qDebug() << "Set platform UserData for body:" << platformBody;

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

void GameWorld::generateLetters(QList<QPoint> letterCoords, QStringList letters) {
    qDebug() << "Letter coordinates size:" << letterCoords.size();
    qDebug() << "Letters size:" << letters.size();

    if (letterCoords.size() != letters.size()) {
        qWarning() << "Mismatch between letter coordinates and letter strings!";
        return;
    }

    letterObjectsList.clear(); // Clear existing letters

    for (int i = 0; i < letterCoords.size(); ++i) {
        LetterObjects letter(letterCoords[i], letters[i]);
        letter.changeImageDimensions(50, 50);

        // Create a static body for the letter
        b2BodyDef letterBodyDef;
        letterBodyDef.type = b2_staticBody;
        letterBodyDef.position.Set(letterCoords[i].x() / SCALE, letterCoords[i].y() / SCALE);

        b2Body* letterBody = world.CreateBody(&letterBodyDef);

        b2PolygonShape letterShape;
        letterShape.SetAsBox(3.0f / SCALE, 3.0f / SCALE); // Half width/height

        b2FixtureDef letterFixtureDef;
        letterFixtureDef.shape = &letterShape;
        letterFixtureDef.density = 0.0f;
        letterBody->CreateFixture(&letterFixtureDef);

        BodyData* letterData = new BodyData{"letter", new LetterObjects(letter)};
        letterBody->SetUserData(letterData);

        letterObjectsList.append(letter);
    }

    update(); // Trigger a repaint
}

void GameWorld::generateTent(){
    // Create the Tent object
    Tent* tent = new Tent();
    levelUpTent = tent; // Store the tent instance for rendering

    // Create a static body in the Box2D world
    b2BodyDef tentBodyDef;
    tentBodyDef.type = b2_staticBody;
    tentBodyDef.position.Set(tent->getBoundingRect().center().x() / SCALE,
                             tent->getBoundingRect().center().y() / SCALE);
    b2Body* tentBody = world.CreateBody(&tentBodyDef);

    // Define the shape for the tent
    b2PolygonShape tentShape;
    tentShape.SetAsBox(tent->getBoundingRect().width() / (3.0f * SCALE),
                       tent->getBoundingRect().height() / (3.0f * SCALE));

    // Define the fixture for the tent
    b2FixtureDef tentFixtureDef;
    tentFixtureDef.shape = &tentShape;
    tentFixtureDef.isSensor = true; // Mark this fixture as a sensor
    tentBody->CreateFixture(&tentFixtureDef);

    // Attach user data for collision handling
    BodyData* tentData = new BodyData("tent", tent);
    tentBody->SetUserData(tentData);

    qDebug() << "Tent created with UserData:" << tentBody;
}




void GameWorld::initializePlayerPosition() {
    QPoint playerPosition(100,0); // Adjust to start above a platform
    qDebug() << "Inside initializePlayerPosition: " << characterType;
    mainPlayer = new mainCharacter(playerPosition, &world, contactListener, characterType);

    BodyData* playerData = new BodyData("player", mainPlayer);
    mainPlayer->getBody()->SetUserData(playerData);
}

void GameWorld::displayPrompt(SurvivalPrompt::Prompt& prompt) {
    // Combine the question and answers into a single string
    QString quizContent = QString(
                              "<b>Question:</b> %1<br><br>"
                              "%2<br>"
                              "%3<br>"
                              "%4<br>"
                              "%5"
                              ).arg(prompt.question)
                              .arg(prompt.optionA)
                              .arg(prompt.optionB)
                              .arg(prompt.optionC)
                              .arg(prompt.optionD);

    qDebug() << "The prompt is being displayed.";
    // Update the label with the formatted content
    promptLabel->setText(quizContent);
}

void GameWorld::checkLetter(QString letter) {
    emit checkLetterInModel(letter); // emits to model to handle the check
}

void GameWorld::handleObstacleCollisions() {
    emit collidedWithObstacle(); // emits to model to handle obstacle collisions
}

