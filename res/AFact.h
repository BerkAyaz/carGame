//
// Created by berka on 11/03/2019.
//

#ifndef GPPROJECT_AFACT_H
#define GPPROJECT_AFACT_H
#include "car.h"
#include "Missile.h"
#include "Enemy.h"
#include "string"
#include "Bonus.h"

class AFact {
public:
    virtual void updateBackground() = 0;
    virtual void render() = 0;

    virtual Car* createCar() = 0;
    virtual Missile* createMissile(int x, int y) = 0;
    virtual Missile* createEnemyMissile(int x, int y) = 0;
    virtual Enemy* createEnemy() = 0;
    virtual Bonus* createBonus(int type) = 0;

    virtual void visLives(int x, int y) = 0;
private:
};


#endif //GPPROJECT_AFACT_H
