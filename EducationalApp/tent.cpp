#include "tent.h"
#include <qDebug>

Tent::Tent() {
    qDebug() << "Inside tent constructor";
    tentPosition = QPoint(1150, 640);
    image = QImage(":/Images/tent.png");
    image = image.scaled(300, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    boundingRect = QRect(tentPosition, image.size());
}

QRect Tent::getBoundingRect() {
    return boundingRect;
}

QImage Tent::getImage() {
    return image;
}

