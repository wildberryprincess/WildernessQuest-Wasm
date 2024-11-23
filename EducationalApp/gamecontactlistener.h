#ifndef GAMECONTACTLISTENER_H
#define GAMECONTACTLISTENER_H

#include <Box2D/Box2D.h>

// A contact listener for detecting collisions in the game world
class GameContactListener : public b2ContactListener {
public:
    bool isGrounded = false;

    // Called when two fixtures begin to touch
    void BeginContact(b2Contact* contact) override;

    // Called when two fixtures cease to touch
    void EndContact(b2Contact* contact) override;

    void setPlayerBody(b2Body* body);

private:
    b2Body* playerBody;
};

#endif // GAMECONTACTLISTENER_H
