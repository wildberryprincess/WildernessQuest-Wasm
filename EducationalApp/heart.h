/*
Authors: Andry Joseph (andry-joseph), Emilie Parra (emilie-parra), Eliza Kitchens (wildberryprincess) & Alexis Brown (alexb000)
Assignment #9: Educational Game
Reviewer: Emilie Parra (.cpp &.h)

This class creates a heart object that is used to visualize how many lives our player has
*/
#ifndef HEART_H
#define HEART_H
#include <QPoint>
#include <QImage>

class Heart
{
public:
    Heart(QPoint position);

    /**
     * @brief getImage :  Will return the QImage object that holds the heart png
     * @return : A QImage object
     */
    QImage getImage();

    /**
     * @brief getPosition : Returns the position of the heart png
     * @return  : A QPoint object with the heart object coordinates
     */
    QPoint getPosition();

private:
    QImage image;
     QPoint position;
};
#endif // HEART_H
