#include "gamecontactlistener.h"
#include "letterobjects.h"
#include "platform.h"
#include "obstacle.h"
#include "maincharacter.h"
#include "gameworld.h"
#include <QDebug>

void GameContactListener::BeginContact(b2Contact* contact) {
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (!bodyUserDataA || !bodyUserDataB) {
        return;
    }

    BodyData* dataA = static_cast<BodyData*>(bodyUserDataA);
    BodyData* dataB = static_cast<BodyData*>(bodyUserDataB);

    // Determine which is the player and which is the other object
    BodyData* playerData = (dataA->type == "player") ? dataA
                           : (dataB->type == "player") ? dataB
                                                       : nullptr;
    BodyData* otherData = (dataA->type == "player") ? dataB
                          : (dataB->type == "player") ? dataA
                                                      : nullptr;

    if (!playerData || !otherData) {
        return;
    }

    if (otherData->type == "platform") {
        isGrounded = true; // Set player as grounded
    } else if (otherData->type == "letter") {
        LetterObjects* letter = static_cast<LetterObjects*>(otherData->object);
        if (letter) {
            collidedLetter = letter->getLetter();
            gameWorld->checkLetter(collidedLetter); // Notify GameWorld
        } else {
            qWarning() << "Null letter object in collision.";
        }
    } else if (otherData->type == "obstacle") {
        Obstacle* obstacle = static_cast<Obstacle*>(otherData->object);
        if (obstacle) {
            collidedObstaclePosition = obstacle->getPosition();
            gameWorld->handleObstacleCollisions(*obstacle);
        } else {
            qWarning() << "Null obstacle object in collision.";
        }
    } else if (otherData->type == "tent") {
        gameWorld->handleTentCollisions();
    } else {
    }
}

void GameContactListener::EndContact(b2Contact* contact) {
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (!bodyUserDataA || !bodyUserDataB) return;

    BodyData* dataA = static_cast<BodyData*>(bodyUserDataA);
    BodyData* dataB = static_cast<BodyData*>(bodyUserDataB);

    // Determine which is the player and which is the other object
    BodyData* playerData = (dataA->type == "player") ? dataA
                           : (dataB->type == "player") ? dataB
                                                       : nullptr;
    BodyData* otherData = (dataA->type == "player") ? dataB
                          : (dataB->type == "player") ? dataA
                                                      : nullptr;

    if (playerData && otherData) {
        if (otherData->type == "platform") {
            isGrounded = false; // Set player as airborne
        } else if (otherData->type == "letter") {
        } else if (otherData->type == "obstacle") {
        } else if (otherData->type == "tent") {
        }
    } else {
    }
}

void GameContactListener::setGameWorld(GameWorld* world) {
    gameWorld = world;
}
