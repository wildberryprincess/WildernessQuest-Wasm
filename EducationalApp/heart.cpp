#include "heart.h"
#include <qDebug>

Heart::Heart(QPoint position) : position(position) {
    qDebug() << "Inside heart constructor";
    image = QImage(":/Images/heart.png");
    image = image.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}


QImage Heart::getImage() {
    return image;
}

QPoint Heart::getPosition() {
    return position;
}
