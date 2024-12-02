#include "tent.h"
#include <qDebug>

Tent::Tent() {
    qDebug() << "Inside tent constructor";
    position = QPoint(1150, 500);
    image = QImage(":/Images/tent.png");
    image = image.scaled(300, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    boundingRect = QRect(position, image.size());
}

QRect Tent::getBoundingRect() {
    return boundingRect;
}

QImage Tent::getImage() {
    return image;
}

