/*
Authors: Andry Joseph (andry-joseph), Emilie Parra (emilie-parra), Eliza Kitchens (wildberryprincess) & Alexis Brown (alexb000)
Assignment #9: Educational Game
Reviewer: Andry Joseph (.cpp &.h)


This file creates a bear "Obstacle" which will be the one and only obstacle the player has to look out for with when navigating the game.
The obstacle is created and displayed in gameWorld and its positions change for each level. Once the character has collided with the bear,
they lose one life and the bear disappears from the screen.
*/

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QPoint>
#include <QImage>

class Obstacle
{
public:

    /**
     * @brief Obstacle: The constructor which creates the obstacle object.
     * @param position: The position of where the bear is drawn.
     */
    Obstacle(const QPoint& position);

    QPoint position;

    /**
     * @brief getBoundingRect: This method gets a bounding rectangle for the bear image which will be used to draw the bear to
     *        the screen and check for collsions.
     * @return The bounding rectangle.
     */
    QRect getBoundingRect();

    /**
     * @brief getImage: This method gets the image set in the obstacle object.
     * @return The image
     */
    QImage getImage();

    /**
     * @brief getPosition: This method gets the position of the obstacle.
     * @return The position
     */
    QPoint getPosition();

    /**
     * @brief operator ==: This method checks if two obstacle are equal to each other.
     * @param other: The obstacle we wan't to compare
     * @return True if they are equal, false if not
     */
    bool operator==(const Obstacle& other) const;

private:
    QRect boundingRect;
    QImage image;
};

#endif // OBSTACLE_H
