#include "bodydata.h"
#include "letterobjects.h"
#include "platform.h"
#include "obstacle.h"
#include "maincharacter.h"
#include "tent.h"
#include <QDebug>

BodyData::BodyData() noexcept : type(""), object(nullptr) {}

BodyData::BodyData(const QString& type, void* object) noexcept : type(type), object(object) {}

BodyData::~BodyData() {
    if (type == "letter") {
        delete static_cast<LetterObjects*>(object);
    } else if (type == "platform") {
        delete static_cast<Platform*>(object);
    } else if (type == "obstacle") {
        delete static_cast<Obstacle*>(object);
    } else if (type == "player") {
        delete static_cast<mainCharacter*>(object);
    } else if (type == "tent") {
        delete static_cast<Tent*>(object);
    } else {
    }
}
