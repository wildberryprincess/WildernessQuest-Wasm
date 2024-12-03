#include "obstacle.h"
#include <QDebug>

Obstacle::Obstacle(const QPoint& position) : position(position) {
    qDebug() << "Inside obstacle Constructor";

    image = QImage(":/Images/bear.png");
    image = image.scaled(60, 60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    boundingRect = QRect(position, image.size());
}

QRect Obstacle::getBoundingRect() {
    return boundingRect;
}

QImage Obstacle::getImage() {
    return image;
}

// QImage Obstacle::
