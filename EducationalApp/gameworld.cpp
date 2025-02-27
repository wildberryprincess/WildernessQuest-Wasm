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
    contactListener(new GameContactListener()),
    promptLabel(new QLabel(this)),
    gameInfoLabel(new QLabel(this)),
    progressBar(new QProgressBar(this))
{
    progressBar->setValue(0);
    progressBar->setMaximum(5); // Adjust this to fit the number of questions per level
    progressBar->setFixedSize(300, 10);
    progressBar->move(15, 75);
    progressBar->setTextVisible(false); // Hide percentage
    progressBar->setStyleSheet(R"(
    QProgressBar {
        border: 2px solid #c1c19e; /* Light blue border */
        border-radius: 15px;
        background-color: #F1FAEE; /* Soft sky color */
    }
    QProgressBar::chunk {
        background-color: #c1c19e; /* Light green (grass-like) chunk */
        border-radius: 8px; /* Rounded edges for the filled portion */
        margin: 2px;
    }
)");

    numOfQuestionsLeft = 0;
    progressLabel = new QLabel(this);
    progressLabel->show();
    progressLabel->move(20, 85);
    progressLabel->setFixedSize(300, 25);
    progressLabel->setStyleSheet("color: black;");


    std::queue<std::function<void()>> deferredActions;

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
    initializeHearts();
    levelUpTent = new Tent();

    world.SetContactListener(contactListener); // Sets the collision detection

    contactListener->setGameWorld(this);

    // Set up the prompt display
    promptLabel->setWordWrap(true);
    promptLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);
    promptLabel->setStyleSheet("font-size: 14px; color: black; font-family: Courier;");
    promptLabel->setGeometry(725, 10, 700, 300);

    // Set up the game info display
    gameInfoLabel->setWordWrap(true);
    gameInfoLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    gameInfoLabel->setStyleSheet("font-size: 24px; color: black; font-family: Courier;");
    gameInfoLabel->setGeometry(5, 0, 375, 250);

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

    // Draw hearts
    for (int i = 0; i < currentLives; ++i) {
        if (i < heartsList.size()) {
            Heart& heart = heartsList[i];
            painter.drawImage(heart.getPosition(), heart.getImage());
        }
    }
}

void GameWorld::updateWorld() {

    // Step the physics world
    world.Step(1.0f / 60.0f, 6, 2);

    // Update the main character's movement
    mainPlayer->update();

    if (!contactListener->collidedLetter.isEmpty()) {
        contactListener->collidedLetter.clear(); // Reset after processing
    }

    // Process deferred actions (e.g., creating new bodies)
    while (!deferredActions.empty()) {
        deferredActions.front()(); // Execute the action
        deferredActions.pop();
    }

    numOfQuestionsLeft = 2;
    progressText = QString::number(numOfQuestionsLeft) + " question to go!";

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

    initializePlayerPosition();
}

void GameWorld::setBackgroundPixMap(QString filepath) {
    if (currentBackground) {
        delete currentBackground;
        currentBackground = nullptr;
    }

    currentBackground = new QPixmap(filepath);

    update();
}

void GameWorld::generatePlatforms(QList<QPoint> positionList, QList<QPoint> sizeList) {
    platformsList.clear();
    for (int i = 0; i < positionList.size(); i++) {
        Platform platform(QPoint(positionList[i].x(), positionList[i].y()));
        platform.changeImageDimensions(sizeList[i].x(), sizeList[i].y());
        platformsList.append(platform);
    }

    createPlatformGrid();
}


void GameWorld::generateObstacles(QList<QPoint> positionList) {
    obstaclesList.clear();

    for (const QPoint& position : positionList) {
        // Create the obstacle
        Obstacle obstacle(position);
        obstaclesList.append(obstacle);

        // Capture position in the lambda for deferred creation
        deferredActions.push([this, position, obstacle]() {
            // Create a static body in the Box2D world
            b2BodyDef obstacleBodyDef;
            obstacleBodyDef.type = b2_staticBody;
            obstacleBodyDef.position.Set(position.x() / SCALE, position.y() / SCALE);
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

            // Add the obstacle to the list of managed bodies
            obstacleBodies.append(std::make_pair(position, obstacleBody));

        });
    }
}

void GameWorld::generateLetters(QList<QPoint> letterCoords, QStringList letters) {

    if (letterCoords.size() != letters.size()) {
        qWarning() << "Mismatch between letter coordinates and letter strings!";
        return;
    }

    letterObjectsList.clear(); // Clear existing letters

    for (int i = 0; i < letterCoords.size(); ++i) {
        LetterObjects letter(letterCoords[i], letters[i]);
        letter.changeImageDimensions(50, 50);

        // Capture the current letter and position explicitly in the lambda
        QPoint position = letterCoords[i];
        deferredActions.push([this, letter, position]() {
            // Create a static body for the letter
            b2BodyDef letterBodyDef;
            letterBodyDef.type = b2_staticBody;
            letterBodyDef.position.Set(position.x() / SCALE, position.y() / SCALE);

            b2Body* letterBody = world.CreateBody(&letterBodyDef);

            b2PolygonShape letterShape;
            letterShape.SetAsBox(2.0f / SCALE, 2.0f / SCALE); // Half width/height

            b2FixtureDef letterFixtureDef;
            letterFixtureDef.shape = &letterShape;
            letterFixtureDef.density = 0.0f;
            letterFixtureDef.isSensor = true; // Mark this fixture as a sensor
            letterBody->CreateFixture(&letterFixtureDef);

            BodyData* letterData = new BodyData{"letter", new LetterObjects(letter)};
            letterBody->SetUserData(letterData);

            letterObjectsList.append(letter);

            // Append the platform position and body to platformBodies
            platformBodies.append(std::make_pair(position, letterBody));
        });
    }

    update(); // Trigger a repaint
}

void GameWorld::createPlatformGrid() {
    for (Platform& platform : platformsList) {
        deferredActions.push([this, platform]() {
            // Calculate the top-left position of the platform
            QPoint position = platform.position; // Assuming platform.position gives the top-left QPoint

            // Calculate center of platform for collision
            float centerX = position.x() + (platform.imageSize.x() / 2.0f);
            float centerY = position.y() + (platform.imageSize.y() / 2.0f);

            // Create a static body in the Box2D world
            b2BodyDef platformBodyDef;
            platformBodyDef.type = b2_staticBody;
            platformBodyDef.position.Set(centerX / SCALE, centerY / SCALE);
            b2Body* platformBody = world.CreateBody(&platformBodyDef);
            BodyData* platformData = new BodyData("platform", new Platform(platform)); // Allocate dynamically
            platformBody->SetUserData(platformData);

            // Define the shape for the platform
            b2PolygonShape platformShape;
            platformShape.SetAsBox(platform.imageSize.x() / (2.0f * SCALE), platform.imageSize.y() / (2.0f * SCALE));

            // Define the fixture for the platform with low friction
            b2FixtureDef platformFixtureDef;
            platformFixtureDef.shape = &platformShape;
            platformFixtureDef.density = 0.0f;
            platformFixtureDef.friction = 0.1f;
            platformBody->CreateFixture(&platformFixtureDef);

            // Append the platform position and body to platformBodies
            platformBodies.append(std::make_pair(position, platformBody));
        });
    }
}

void GameWorld::generateTent() {
    deferredActions.push([this]() {
        levelUpTent = new Tent();

        b2BodyDef tentBodyDef;
        tentBodyDef.type = b2_staticBody;
        tentBodyDef.position.Set((levelUpTent->getBoundingRect().x() + levelUpTent->getBoundingRect().width() / 2.0f) / SCALE,
                                 (levelUpTent->getBoundingRect().y() + levelUpTent->getBoundingRect().height() / 2.0f) / SCALE);
        b2Body* tentBody = world.CreateBody(&tentBodyDef);

        b2PolygonShape tentShape;

        // Fine-tuned dimensions for the collision box
        float widthFactor = 0.4f;  // Adjust this to shrink width
        float heightFactor = 0.6f; // Adjust this to shrink height
        tentShape.SetAsBox((levelUpTent->getBoundingRect().width() * widthFactor) / (2.0f * SCALE),
                           (levelUpTent->getBoundingRect().height() * heightFactor) / (2.0f * SCALE));

        b2FixtureDef tentFixtureDef;
        tentFixtureDef.shape = &tentShape;
        tentFixtureDef.isSensor = true;
        tentBody->CreateFixture(&tentFixtureDef);

        BodyData* tentData = new BodyData("tent", levelUpTent);
        tentBody->SetUserData(tentData);

    });
}

void GameWorld::initializePlayerPosition() {
    QPoint playerPosition(100,400); // Adjust to start above a platform
    mainPlayer = new mainCharacter(playerPosition, &world, contactListener, characterType);

    BodyData* playerData = new BodyData("player", mainPlayer);
    mainPlayer->getBody()->SetUserData(playerData);

    b2Vec2 initialBodyPosition = mainPlayer->getBody()->GetPosition();
}

void GameWorld::initializeHearts() {
    heartsList.clear();

    // Fixed positions for the hearts
    int startX = 95; // Starting x-coordinate
    int startY = 25; // Fixed y-coordinate
    int spacing = 60; // Spacing between hearts

    for (int i = 0; i < currentLives; ++i) {
        QPoint position(startX + i * spacing, startY);
        heartsList.append(Heart(position));
    }
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

    // Update the label with the formatted content
    promptLabel->setText(quizContent);
}

void GameWorld::displayGameInfo(int level) {
    QString levelString =
        "<span style='color: black; font-weight: bold;'>Wilderness Quest: Level </span>"
        "<span style='font-weight: bold;'>" + QString::number(level) + "</span>"
                                   "<br><span style='color: black; font-weight: bold;'>Lives: </span>";
    gameInfoLabel->setText(levelString);
}

void GameWorld::updateLivesDisplay(int lives) {
    currentLives = lives;  // Update the local state of lives
    update();
}

void GameWorld::checkLetter(QString letter) {
    emit checkLetterInModel(letter); // emits to model to handle the check
}

void GameWorld::handleIncorrectCollidedLetter() {
    if (!promptLabel) {
        qWarning() << "promptLabel is not initialized!";
        return;
    }

    static QTimer* timer = nullptr;

    if (!timer) {
        // Create the timer if it doesn't exist
        timer = new QTimer(this);
        timer->setSingleShot(true);

        // Restore the original text when the timer times out
        connect(timer, &QTimer::timeout, this, [this]() {
            QString currentText = promptLabel->text();
            // Remove the "Try again!" portion from the text
            int index = currentText.indexOf("<br><br><span style='color: red; font-weight: bold;'>Try again!</span>");
            if (index != -1) {
                currentText = currentText.left(index);
                promptLabel->setText(currentText);
            }
        });
    }

    // Append or overwrite the "Try again!" message
    QString currentText = promptLabel->text();
    int index = currentText.indexOf("<br><br><span style='color: red; font-weight: bold;'>Try again!</span>");
    if (index != -1) {
        currentText = currentText.left(index); // Remove existing "Try again!" message
    }
    QString updatedText = currentText + "<br><br><span style='color: red; font-weight: bold;'>Try again!</span>";
    promptLabel->setText(updatedText);

    timer->start(3000);
}

void GameWorld::handleCorrectCollidedLetter() {
    if (!promptLabel) {
        qWarning() << "promptLabel is not initialized!";
        return;
    }

    static QTimer* timer = nullptr;

    if (!timer) {
        // Create the timer if it doesn't exist
        timer = new QTimer(this);
        timer->setSingleShot(true);

        // Restore the original text when the timer times out
        connect(timer, &QTimer::timeout, this, [this]() {
            QString currentText = promptLabel->text();
            // Remove the "Good job!" portion from the text
            int index = currentText.indexOf("<br><br><span style='color: green; font-weight: bold;'>Good job!</span>");
            if (index != -1) {
                currentText = currentText.left(index);
                promptLabel->setText(currentText);
            }
        });
    }

    // Append or overwrite the "Good job!" message
    QString currentText = promptLabel->text();
    int index = currentText.indexOf("<br><br><span style='color: green; font-weight: bold;'>Good job!</span>");
    if (index != -1) {
        currentText = currentText.left(index); // Remove existing "Good job!" message
    }

    QString updatedText = currentText + "<br><br><span style='color: green; font-weight: bold;'>Good job!</span>";
    promptLabel->setText(updatedText);

    timer->start(3000);
}

void GameWorld::handleProceedToNextLevel() {
    QString currentText = promptLabel->text();
    QString updatedText = currentText +  "<br><br><span style='color: green; font-weight: bold;'>You've completed all of the questions for this level! Now, run to the tent!</span>";
    promptLabel->setText(updatedText);
}

void GameWorld::removeExistingPlatforms() {
    for (int i = platformBodies.size() - 1; i >= 0; --i) {
        b2Body* body = platformBodies[i].second;
        deferredActions.push([this, body, i]() mutable {
            if (i < platformBodies.size()) { // Ensure the index is still valid
                world.DestroyBody(body); // Destroy the body
                platformBodies.removeAt(i); // Remove the entry from the vector
            }
        });
    }
}

void GameWorld::removeExistingLetters() {
    for(int i = letterBodies.size() - 1; i >=0; --i) {
        b2Body* body = letterBodies[i].second;
        deferredActions.push([this, body, i]() mutable {
            if (i < letterBodies.size()) {
                world.DestroyBody(body);
                letterBodies.removeAt(i);
            }
        });
    }
}

void GameWorld::removeExistingObstacles() {
    for(int i = obstacleBodies.size() - 1; i >=0; --i) {
        b2Body* body = obstacleBodies[i].second;
        deferredActions.push([this, body, i]() mutable {
            if (i < obstacleBodies.size()) {
                world.DestroyBody(body);
                obstacleBodies.removeAt(i);
            }
        });
    }
}

void GameWorld::handleObstacleCollisions(Obstacle obstacle) {
    QPoint obstaclePosition = obstacle.getPosition();

    // Remove the obstacle from the list
    obstaclesList.removeAll(obstacle);

    for (int i = 0; i < obstacleBodies.size(); ++i) {
        if (obstacleBodies[i].first == obstaclePosition) {
            b2Body* body = obstacleBodies[i].second;
            int index = i;
            deferredActions.push([this, body, index]() mutable {
                world.DestroyBody(body);
                obstacleBodies.removeAt(index);
            });
            break;
        }
    }

    emit collidedWithObstacle(obstaclePosition); // Notify model of the collision

    update();
}

void GameWorld::handleTentCollisions() {
    emit collidedWithTent();
}

void GameWorld::changeProgressBar(int numAnswered) {
    progressBar->setValue(numAnswered);

    numOfQuestionsLeft = 5 - numAnswered;
    if (numOfQuestionsLeft < 0) {
        numOfQuestionsLeft = 0;
    }

    progressText = QString::number(numOfQuestionsLeft) + " questions to go!";
    QFont courierFont("Courier", 12);
    progressLabel->setFont(courierFont);
    progressLabel->setText(progressText);
}

void GameWorld::setProgressBarToZero() {
    progressBar->setValue(0);
    progressLabel->setText("5 questions to go!");
    QFont courierFont("Courier", 12); // Font: Courier, size: 12
    progressLabel->setFont(courierFont);
}

