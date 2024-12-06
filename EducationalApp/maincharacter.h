/*
Authors: Andry Joseph (andry-joseph), Emilie Parra (emilie-parra), Eliza Kitchens (wildberryprincess) & Alexis Brown (alexb000)
Assignment #9: Educational Game
Reviewer: Andry Joseph (.cpp &.h)


This file creates a "MainCharacter" which will hold the infomation stored for our main scout which will be used to play and interact
with our game. Main Character is one of the main recipients with contactListener as it collides with other objects in the game.
The main character moves around the window using the arrows keys. And based on the main character's position on the screen different
elements are activated.
*/

#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H

#include <QPoint>
#include <QImage>
#include <QString>
#include <Box2D/Box2D.h>
#include <QKeyEvent>
#include "gamecontactlistener.h"

class GameContactListener;
class mainCharacter
{
public:

    /**
     * @brief mainCharacter: The constructor which will create the mainCharacter object.
     * @param position: The poistion the main character wull start at.
     * @param world: Box2D element necessary for jumps.
     * @param contactListener: Allows collisions checks.
     * @param characterType: Value that indicates which scout the player has chosen to play with.
     */
    mainCharacter(const QPoint& position, b2World* world, GameContactListener* contactListener, int characterType);

    /**
     * @brief getBoundingRect: This method gets a bounding rectangle for the character image which will be used to draw the character to
     *        the screen and check for collsions.
     * @return The bounding rectangle.
     */
    QRect getBoundingRect();

    /**
     * @brief getImage: This method gets the image set in the mainCharacter object.
     * @return The image
     */
    QImage getImage();

    /**
     * @brief update: This method updates the character's position and state.
     */
    void update();

    /**
     * @brief keyPressEvent: This methid handles key press events for character movement.
     * @param event: The key press event
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief keyReleaseEvent: This method handles the key release events to stop character movement
     * @param event: The key press event
     */
    void keyReleaseEvent(QKeyEvent *event);

    /**
     * @brief jump: This method allows the main character to jump up.
     */
    void jump();

    /**
     * @brief getBody: This method gets the body type.
     * @return The body
     */
    b2Body* getBody();

private:
    QRect boundingRect;
    QImage image;

    // Flags for key states
    bool moveLeft = false;
    bool moveRight = false;
    bool isJumping = false;
    float verticalVelocity;

    GameContactListener* contactListener; // Pointer to the contact listener

    const float moveSpeed = 5.0f; // Adjust as needed
    b2Body* body;
};

#endif // MAINCHARACTER_H
