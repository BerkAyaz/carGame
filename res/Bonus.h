//
// Created by berka on 23/08/2019.
//

#ifndef CARGAME_BONUS_H
#define CARGAME_BONUS_H

#include "Entity.h"
#include "string"

class Bonus: public Entity {
public:
    Bonus();
    virtual void Vis() = 0;

    void move();
    std::string m_type;
private:
    const int m_speed = 2;

};


#endif //CARGAME_BONUS_H
