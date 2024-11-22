#include "platform.h"

#include <QDebug>
Platforms::Platforms(const QPoint& position) {
    qDebug() << "Inside platform constructor";
    image = QImage(":/images/log.png");
    if (image.isNull()) {
        qDebug() << "Failed to load log.png from resource path.";
    } else {
        qDebug() << "Platform image loaded successfully. Size:" << image.size();
    }
    boundingRect = QRect(position, image.size());
}


QRect Platforms::getBoundingRect(){
    return boundingRect;
}

QImage Platforms::getImage(){
    return image;
}
