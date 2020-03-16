//
// Created by berka on 11/08/2019.
//

#ifndef CARGAME_MISSILE_H
#define CARGAME_MISSILE_H


#include <string>
#include "Entity.h"

class Missile: public Entity{
public:
    Missile(int x, int y, std::string direction);
    ~Missile();

    void move();
    virtual void Vis() = 0;

    std::string m_missileDirection;

private:
    const int m_missileSpeed = 15;
};


#endif //CARGAME_MISSILE_H
