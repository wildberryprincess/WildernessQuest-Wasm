#ifndef BODYDATA_H
#define BODYDATA_H

#include <QString>

struct BodyData {
    QString type;  // e.g., "platform", "letter", "obstacle"
    void* object;  // Pointer to the actual object

    // Default constructor
    BodyData() noexcept;

    // Parameterized constructor
    BodyData(const QString& type, void* object) noexcept;

    ~BodyData();  // Destructor
};

#endif // BODYDATA_H
