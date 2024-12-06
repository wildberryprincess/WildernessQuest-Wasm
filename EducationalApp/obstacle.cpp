#include "obstacle.h"

Obstacle::Obstacle(const QPoint& position) : position(position) {
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

QPoint Obstacle::getPosition() {
    return position;
}

bool Obstacle::operator==(const Obstacle& other) const {
    return this->position == other.position; // Compare based on position
}
