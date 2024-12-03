/*
 *
Authors: Andry Joseph (andry-joseph), Emilie Parra (emilie-parra), Eliza Kitchens (wildberryprincess) & Alexis Brown (alexb000)
Assignment #9: Educational Game
Reviewer: Alexis Brown (.cpp &.h)

LetterObjects is used to create the letter objects "A", "B", "C", "D", that are displayed on the screen.
It sets and returns the image depending on the specific letter. It also allows you to retrieve
the specific letter, as well as change the image dimmensions.
*/

#ifndef LETTEROBJECTS_H
#define LETTEROBJECTS_H

#include <QPoint>
#include <QImage>
#include <QString>

class LetterObjects
{
public:
    /**
     * @brief LetterObjects : constructor to create the LetterObject
     * @param position : the position of the letter on the screen
     * @param letter : the actual letter itself e.g. "A", "B", "C", D"
     */
    LetterObjects(const QPoint& position, const QString& letter); // Constructor to specify position and letter

    /**
     * @brief getBoundingRect : Returns the bounding rectangle based on the image size.
     * It is useful for collision logic
     * @return : The bounding rectangle of the letter
     */
    QRect getBoundingRect();

    /**
     * @brief changeImageDimensions : Allows the size of the image to be changed
     * @param newWidth : New width of the image
     * @param newHeight : New height of the image
     */
    void changeImageDimensions(int newWidth, int newHeight);

    /**
     * @brief getImage : Retrieves the image of the specific letter
     * @return : The image
     */
    QImage getImage();

    /**
     * @brief getLetter : Retrieves the actual letter
     * @return A QString of letter "A", "B", "C", or "D"
     */
    QString getLetter();


private:
    QRect boundingRect;
    QImage image;
    QString objectLetter;
    QPoint position;
    QPoint imageSize;
};

#endif // LETTEROBJECTS_H
