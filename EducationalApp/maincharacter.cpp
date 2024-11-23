#include "maincharacter.h"

mainCharacter::mainCharacter(const QPoint& position){
    image = QImage(":/Images/hero.png");
    boundingRect = QRect(position, image.size());
}

    // gets the boundary of the character which is helpful for collisions
QRect mainCharacter::getBoundingRect(){
    return boundingRect;
}
QImage mainCharacter::getImage(){
    return image;
}
