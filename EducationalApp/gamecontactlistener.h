/*
Authors: Andry Joseph (andry-joseph), Emilie Parra (emilie-parra), Eliza Kitchens (wildberryprincess) & Alexis Brown (alexb000)
Assignment #9: Educational Game
Reviewer: Alexis Brown (.cpp &.h)

GameContactListener if a custom implementation of Box2D's b2ContactListener.
It is meant to detect and handle collisions between objects in the game. It manages interactions by
identifying when objects collide and triggering the necessary responses based on the type of object involved.
A custom b2ContactListener allows us to definine specific actions for different types of collisions
and allows us to integrate custom data structures like BodyData to distinguish between object types.
*/

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
class GameContactListener : public b2ContactListener {
public:
    bool isGrounded = false; // Bool to notify when the user is in contact with an object

    /**
     * @brief BeginContact : This is called when two obects are in contact with each other (a collision)
     * @param contact : provides access to the details about which objects are involved,
     * their physical properties, and state of the collision
     */
    void BeginContact(b2Contact* contact) override;

    /**
     * @brief EndContact : This is called when two objects are no longer in contact with each other
     * @param contact : Same as above, provides access to details about the objects that are colliding
     */
    void EndContact(b2Contact* contact) override;

    /**
     * @brief setGameWorld: sets the GameWorld as the current world
     * @param world : the current world that the program is using
     */
    void setGameWorld(GameWorld* world);

    QString collidedLetter; // Stores the letter the player collided with
    QPoint collidedObstaclePosition;

private:
    b2Body* playerBody;
    GameWorld* gameWorld;
};

#endif // GAMECONTACTLISTENER_H
