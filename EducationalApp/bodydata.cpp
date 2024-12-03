#include "bodydata.h"
#include "letterobjects.h"
#include "platform.h"
#include "obstacle.h"
#include "maincharacter.h"
#include "tent.h"
#include <QDebug>

// Default constructor
BodyData::BodyData() noexcept : type(""), object(nullptr) {}

// Parameterized constructor
BodyData::BodyData(const QString& type, void* object) noexcept : type(type), object(object) {}

// Destructor
BodyData::~BodyData() {
    if (type == "letter") {
        qDebug() << "Deleting LetterObjects.";
        delete static_cast<LetterObjects*>(object);
    } else if (type == "platform") {
        qDebug() << "Cleaning up Platform data (if dynamically allocated).";
        delete static_cast<Platform*>(object);
    } else if (type == "obstacle") {
        qDebug() << "Deleting Obstacle.";
        delete static_cast<Obstacle*>(object);
    } else if (type == "player") {
        qDebug() << "Deleting MainCharacter.";
        delete static_cast<mainCharacter*>(object);
    } else if (type == "tent") {
        qDebug() << "Deleting Tent.";
        delete static_cast<Tent*>(object);
    } else {
        qDebug() << "Unknown type in BodyData, no cleanup performed.";
    }
    qDebug() << "Inside bodydata.cpp destructor";
}
