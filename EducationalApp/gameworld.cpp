#include "gameworld.h"
#include "maincharacter.h"
#include "obstacle.h"
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <cstdlib>
#define SCALE 30.0f

GameWorld::GameWorld(QWidget *parent)
    : QWidget(parent),
    world(b2Vec2(0.0f, 10.0f)),
    timer(this),
    currentBackground(nullptr),
    promptLabel(new QLabel(this))
{

    // Ensure GameWorld has focus to handle key events
    setFocusPolicy(Qt::StrongFocus);

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

    // Set up the prompt display
    promptLabel->setWordWrap(true);
    promptLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);
    promptLabel->setStyleSheet("font-size: 16px; color: black; font-family: Arial;");
    promptLabel->setGeometry(725, 10, 500, 150);

    // Set up the timer for the game loop
    connect(&timer, &QTimer::timeout, this, &GameWorld::updateWorld);
    timer.start(10);
}


void GameWorld::paintEvent(QPaintEvent *) {

    QPainter painter(this);

    if (currentBackground) {
        if (!currentBackground->isNull()) {
            qDebug() << "Drawing valid background";
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

    if (currentBackground) {
        delete currentBackground;
        currentBackground = nullptr;
    }

    currentBackground = new QPixmap(filepath);

    update(); // This triggers a repaint
}

void GameWorld::generatePlatforms(QList<QPoint> positionList, QList<QPoint> sizeList) {

    for (int i = 0; i < 10; i++) {
        Platform platform(QPoint(positionList[i].x(), positionList[i].y()));
        platform.changeImageDimensions(sizeList[i].x(), sizeList[i].y());
        platformsList.append(platform);
    }
    createPlatformGrid();
}

void GameWorld::generateObstacles(QList<QPoint> positionList) {
    qDebug() << "Obstacle list size: " << positionList.size();
    for (int i = 0; i < 3; i++) {
        Obstacle obstacle(QPoint(positionList[i].x(), positionList[i].y()));
        obstaclesList.append(obstacle);
    }

    // Obstacle obstacle(QPoint(850, 550));
    // obstaclesList.append(obstacle);
}

void GameWorld::createPlatformGrid() {

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

void GameWorld::generateLetters(QList<QPoint> letterCoords, QStringList letters) {
    qDebug() << "Letter coordinates size:" << letterCoords.size();
    qDebug() << "Letters size:" << letters.size();

    if (letterCoords.size() != letters.size()) {
        qWarning() << "Mismatch between letter coordinates and letter strings!";
        return;
    }

    letterObjectsList.clear(); // Clear existing letters

    for (int i = 0; i < letterCoords.size(); ++i) {
        LetterObjects letter(letterCoords[i], letters[i]); // Use both the position and letter
        letter.changeImageDimensions(50, 50); // Resize letter to fit on screen
        letterObjectsList.append(letter);
    }
    update(); // Trigger a repaint
}



void GameWorld::initializePlayerPosition() {
    QPoint playerPosition(100,0); // Adjust to start above a platform
    mainPlayer = new mainCharacter(playerPosition, &world, &contactListener);
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


