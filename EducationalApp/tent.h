/*
Authors: Andry Joseph (andry-joseph), Emilie Parra (emilie-parra), Eliza Kitchens (wildberryprincess) & Alexis Brown (alexb000)
Assignment #9: Educational Game
Reviewer: Emilie Parra (.cpp &.h)

This class creates a tent object to display in the game and allow for interaction between the tent and our player
to be able to move on to the next level
*/
#ifndef TENT_H
#define TENT_H

#include <QPoint>
#include <QImage>

class Tent
{
public:
    Tent();
    QPoint tentPosition;

    /**
     * @brief getBoundingRect : The bounding rect of the tent object is what our main character will interact
     * with and collide with
     * @return : The bounding rect which is defined by the position and size of the tent image
     */
    QRect getBoundingRect();

    /**
     * @brief getImage : Will return the QImage object that holds the tent png
     * @return : A QImage object
     */
    QImage getImage();

private:
    QRect boundingRect;
    QImage image;
};

#endif // TENT_H
