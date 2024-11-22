#include "platforms.h"

Platforms::Platforms(const QPoint& position) {
    image = image = QImage(":/images/log.png");
    boundingRect = QRect(position, image.size());
}

QRect Platforms::getBoundingRect(){
    return boundingRect;
}

QImage Platforms::getImage(){
    return image;
}
