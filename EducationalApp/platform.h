/*
Authors: Andry Joseph (andry-joseph), Emilie Parra (emilie-parra), Eliza Kitchens (wildberryprincess) & Alexis Brown (alexb000)
Assignment #9: Educational Game
Reviewer: Andry Joseph (.cpp &.h)


This file creates a "platform" which will hold the information of the platform that the player will move around on. Each platform
created has a fixed position and size which will be set for each level and redrawn when the player advances. The platforms will
have their own physics elements which will allow the main character to interact with it more efficiently.
*/

#ifndef PLATFORMS_H
#define PLATFORMS_H

#include <QPoint>
#include <QImage>

class Platform
{
public:

    /**
     * @brief Platform: The constructor which will create the Platform object
     * @param position: The position of the platform
     */
    Platform(const QPoint& position);

    QPoint position;
    QPoint imageSize;

    /**
     * @brief getBoundingRect: This method gets a bounding rectangle for the platform image which will be used to draw the platform to
     *        the screen and check for collsions.
     * @return The bounding rectangle.
     */
    QRect getBoundingRect();

    /**
     * @brief changeImageDimensions: This method allows us to change the dimensions of the platform later on.
     * @param newWidth: The new width of the platform
     * @param newHeight: The new height of the platform
     */
    void changeImageDimensions(int newWidth, int newHeight);

    /**
     * @brief getImage: This method gets the image set in the platform object.
     * @return The image
     */
    QImage getImage();

private:
    QRect boundingRect;
    QImage image;
};

#endif // PLATFORMS_H
