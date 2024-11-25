#include "platform.h"

#include <QDebug>
Platform::Platform(const QPoint& position) {
    qDebug() << "Inside platform constructor";
    image = QImage(":/Images/log2.0.png");

    if (image.isNull()) {
        qDebug() << "Failed to load log.png from resource path.";
    } else {
        qDebug() << "Platform image loaded successfully. Size:" << image.size();
    }
    boundingRect = QRect(position, image.size());
}


QRect Platform::getBoundingRect(){
    return boundingRect;
}

void Platform::changeImageDimensions(int newWidth, int newHeight){
    image = image.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

QImage Platform::getImage() {
    return image;
}
