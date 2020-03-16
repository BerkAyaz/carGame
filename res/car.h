//
// Created by berka on 11/03/2019.
//

#ifndef GPPROJECT_CAR_H
#define GPPROJECT_CAR_H

#include <string>
#include "Entity.h"


class Car: public Entity {

public:
    Car();

    void move(std::string direction);

    virtual void setCartexture(std::string path) = 0;

    int m_currentAmmoSize = 10;
    const int m_maxAmmoSize = 10;
    int m_lives = 5;

private:
    const int m_speed = 10;

};


#endif //GPPROJECT_CAR_H
