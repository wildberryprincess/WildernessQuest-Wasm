#ifndef LETTEROBJECTS_H
#define LETTEROBJECTS_H

#include <QPoint>
#include <QImage>
#include <QString>

class LetterObjects
{
public:
    LetterObjects(const QPoint& position, const QString& letter); // Constructor to specify position and letter
    QPoint position;
    QPoint imageSize;

    // Gets the boundary of the letter object, useful for collisions
    QRect getBoundingRect();
    void changeImageDimensions(int newWidth, int newHeight);
    QImage getImage();
    QString getLetter();

private:
    QRect boundingRect;
    QImage image;
    QString objectLetter;
};

#endif // LETTEROBJECTS_H
