#include "gamecontactlistener.h"
#include "letterobjects.h"
#include "platform.h"
#include "obstacle.h"
#include "maincharacter.h"
#include "gameworld.h" // Include the full definition of GameWorld
#include <QDebug>

void GameContactListener::BeginContact(b2Contact* contact) {
    qDebug() << "BeginContact triggered";

    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (!bodyUserDataA || !bodyUserDataB) {
        qWarning() << "One of the bodies has no UserData.";
        return;
    }

    BodyData* dataA = static_cast<BodyData*>(bodyUserDataA);
    BodyData* dataB = static_cast<BodyData*>(bodyUserDataB);

    // Determine which is the player and which is the other object
    BodyData* playerData = (dataA->type == "player") ? dataA : (dataB->type == "player") ? dataB : nullptr;
    BodyData* otherData = (dataA->type == "player") ? dataB : (dataB->type == "player") ? dataA : nullptr;

    if (!playerData || !otherData) {
        qWarning() << "Invalid BodyData detected.";
        return;
    }

    if (otherData->type == "platform") {
        isGrounded = true; // Set player as grounded
        qDebug() << "Player is grounded on a platform.";
    } else if (otherData->type == "letter") {
        LetterObjects* letter = static_cast<LetterObjects*>(otherData->object);
        if (letter) {
            collidedLetter = letter->getLetter();
            gameWorld->checkLetter(collidedLetter); // Notify GameWorld
            qDebug() << "Player collected letter:" << collidedLetter;
        } else {
            qWarning() << "Null letter object in collision.";
        }
    } else if (otherData->type == "obstacle") {
        gameWorld->handleObstacleCollisions();
        qDebug() << "Player collided with an obstacle!";
    }
        else if (otherData->type == "tent") {
            gameWorld->handleTentCollisions();
            qDebug() << "Player collided with a tent!";
        }
     else {
        qWarning() << "Unknown collision type:" << otherData->type;
    }
}


void GameContactListener::EndContact(b2Contact* contact) {
    qDebug() << "EndContact triggered";

    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (!bodyUserDataA || !bodyUserDataB) return;

    BodyData* dataA = static_cast<BodyData*>(bodyUserDataA);
    BodyData* dataB = static_cast<BodyData*>(bodyUserDataB);

    // Determine which is the player and which is the other object
    BodyData* playerData = (dataA->type == "player") ? dataA : (dataB->type == "player") ? dataB : nullptr;
    BodyData* otherData = (dataA->type == "player") ? dataB : (dataB->type == "player") ? dataA : nullptr;

    if (playerData && otherData) {
        if (otherData->type == "platform") {
            isGrounded = false; // Set player as airborne
            qDebug() << "Player is no longer grounded on a platform.";
        } else if (otherData->type == "letter") {
            qDebug() << "Player is no longer in contact with a letter.";
        } else if (otherData->type == "obstacle") {
            qDebug() << "Player is no longer in contact with an obstacle.";
        } else if (otherData->type == "tent") {
            qDebug() << "Player is no longer in contact with a tent.";
        }
    } else {
        qDebug() << "Collision ended but not involving player.";
    }
}


void GameContactListener::setPlayerBody(b2Body* body) {
    playerBody = body;
}

void GameContactListener::setGameWorld(GameWorld* world) {
    gameWorld = world;
}



