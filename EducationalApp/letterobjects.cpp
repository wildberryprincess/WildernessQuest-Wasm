#include "letterobjects.h"

LetterObjects::LetterObjects(const QPoint& position, const QString& letter)
    : position(position)
{
    // Load the image based on the letter
    if (letter == "a") {
        image = QImage(":/Images/a.png");
    } else if (letter == "b") {
        image = QImage(":/Images/b.png");
    } else if (letter == "c") {
        image = QImage(":/Images/c.png");
    } else if (letter == "d") {
        image = QImage(":/Images/d.png");
    } else {
        image = QImage(); // Empty image for invalid letters
    }

    // Set the bounding rectangle based on the image size and position
    boundingRect = QRect(position, image.size());
}

QRect LetterObjects::getBoundingRect() {
    return boundingRect;
}

void LetterObjects::changeImageDimensions(int newWidth, int newHeight) {
    // Resize the image and update the bounding rectangle
    image = image.scaled(newWidth, newHeight, Qt::KeepAspectRatio);
    boundingRect.setSize(image.size());
}

QImage LetterObjects::getImage() {
    return image;
}
