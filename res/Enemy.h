//
// Created by berka on 11/08/2019.
//

#ifndef CARGAME_ENEMY_H
#define CARGAME_ENEMY_H

#include "Entity.h"

class Enemy: public Entity{
public:
    Enemy();
    ~Enemy();

    void setSpawn();
    void move();

    void reload();

    bool m_canShoot = false;

    int m_currentShoot, m_lastShoot;

private:
    const int m_reloadTime = 1500;
    const int m_speed = 4;

};


#endif //CARGAME_ENEMY_H
