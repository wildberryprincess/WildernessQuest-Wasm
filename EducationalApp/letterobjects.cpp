#include "letterobjects.h"

LetterObjects::LetterObjects(const QPoint& position, const QString& letter)
    : position(position) {
    // Load the image based on the letter
    if (letter == "a") {
        image = QImage(":/Images/A.png");
    } else if (letter == "b") {
        image = QImage(":/Images/B.png");
    } else if (letter == "c") {
        image = QImage(":/Images/C.png");
    } else if (letter == "d") {
        image = QImage(":/Images/D.png");
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
    imageSize.setX(newWidth);
    imageSize.setY(newHeight);
    image = image.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    boundingRect.setSize(image.size());
}

QImage LetterObjects::getImage() {
    return image;
}
