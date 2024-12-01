#ifndef GAMECONTACTLISTENER_H
#define GAMECONTACTLISTENER_H

#include <Box2D/Box2D.h>
#include <QString>
#include "letterobjects.h"
#include "platform.h"
#include "obstacle.h"
#include "maincharacter.h"
#include "bodydata.h"
#include <QDebug>

class GameWorld;
// A contact listener for detecting collisions in the game world
class GameContactListener : public b2ContactListener {
public:
    bool isGrounded = false;

    // Called when two fixtures begin to touch
    void BeginContact(b2Contact* contact) override;

    // Called when two fixtures cease to touch
    void EndContact(b2Contact* contact) override;

    void setPlayerBody(b2Body* body);
    void setGameWorld(GameWorld* world);

    QString collidedLetter; // Stores the letter the player collided with

private:
    b2Body* playerBody;
    GameWorld* gameWorld;
};

#endif // GAMECONTACTLISTENER_H
