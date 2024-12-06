#include "platform.h"

Platform::Platform(const QPoint& position) : position(position) {
    image = QImage(":/Images/log2.0.png");
    boundingRect = QRect(position, image.size());
}

QRect Platform::getBoundingRect(){
    return boundingRect;
}

void Platform::changeImageDimensions(int newWidth, int newHeight){
    imageSize.setX(newWidth);
    imageSize.setY(newHeight);
    image = image.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

QImage Platform::getImage() {
    return image;
}
