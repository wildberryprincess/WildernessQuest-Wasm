/*
Authors: Andry Joseph (andry-joseph), Emilie Parra (emilie-parra), Eliza Kitchens (wildberryprincess) & Alexis Brown (alexb000)
Assignment #9: Educational Game
Reviewer: Alexis Brown (.cpp &.h)


This file creates a "BodyData" struct that is used to store the name of an object, as well as it's type. It is used primarily
inside of GameContactListener so that the contact listener can identity the type of object the user has colliding with.
Because Box2D dosent inherently know the types of objects involved in a collsions, BodyData is a way to store the necessary information.
While body data is a struct, it behaves as an object and stores the platform, main character, tent, and obstacle data.
*/
#ifndef BODYDATA_H
#define BODYDATA_H

#include <QString>

struct BodyData {
    QString type;  // e.g., "platform", "letter", "obstacle"
    void* object;  // Pointer to the actual object

    /**
     * @brief BodyData : default constructor
     */
    BodyData() noexcept;

    /**
     * @brief BodyData : paramaterized constructor
     * @param type : name of the object being stored ("platform", "obstacle", etc.)
     * @param object : the actual object itself
     */
    BodyData(const QString& type, void* object) noexcept;

    /**
     * @brief ~BodyData : Destructor that handles the save removal of BodyData objects
     */
    ~BodyData();  // Destructor
};

#endif // BODYDATA_H
