#include "gamecontactlistener.h"
#include<QDebug>

void GameContactListener::BeginContact(b2Contact* contact) {
    qDebug() << "BeginContact triggered";

    void* bodyUserDataA = contact->GetFixtureA()->GetBody();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody();

    if (bodyUserDataA == playerBody || bodyUserDataB == playerBody) {
        isGrounded = true;
        qDebug() << "Player is grounded.";
    } else {
        qDebug() << "Collision detected but not with player.";
    }
}

void GameContactListener::EndContact(b2Contact* contact) {
    qDebug() << "EndContact triggered";

    void* bodyUserDataA = contact->GetFixtureA()->GetBody();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody();

    if (bodyUserDataA == playerBody || bodyUserDataB == playerBody) {
        isGrounded = false;
        qDebug() << "Player is airborne.";
    } else {
        qDebug() << "Collision ended but not with player.";
    }
}


void GameContactListener::setPlayerBody(b2Body* body) {
    playerBody = body;
}

