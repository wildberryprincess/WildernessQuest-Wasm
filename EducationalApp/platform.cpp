#include "platform.h"

#include <QDebug>
Platform::Platform(const QPoint& position) {
    qDebug() << "Inside platform constructor";
    image = QImage(":/Images/log2.png");
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

QImage Platform::getImage(){
    return image;
}
