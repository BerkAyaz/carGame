//
// Created by berka on 11/03/2019.
//

#ifndef GPPROJECT_GAME_H
#define GPPROJECT_GAME_H
#include "AFact.h"
#include "eventHandler.h"
#include <list>
namespace game
{
    const int SCREEN_WIDTH=550;
    const int SCREEN_HEIGHT=750;
}

class Game {

public:
    Game(AFact* aFactory, eventHandler* eH);
    ~Game();

    void start();
    void handleEvent();
    void renderGame();

    void addMissile();
    void addEnemy();
    void addEnemyMissile(Enemy *e);
    void addBonus();

    bool checkCollision(Entity *a, Entity *b);

    void loadConfig();
    void saveConfig();
    static Game* getInstance(AFact* aFactory, eventHandler* eH);
private:
    static Game* m_instance;

    int m_enemyCount = 0;

    int m_score = 0;

    int m_highScore;
    std::string m_carSkin;

    const int m_maxSpawnTime = 2000;
    const int m_maxReloadTime = 3000;
    const int m_maxBonusTime = 6000;
    const int m_maxInvincibleTime = 6000;

    Car* m_car;
    std::list<Missile*> m_missiles;
    std::list<Enemy*> m_enemies;
    std::list<Missile*> m_enemyMissiles;
    std::list<Bonus*> m_bonusses;

    eventHandler* m_eventHandler;
    AFact* m_aFactory;

    bool m_invincible = false;
};


#endif //GPPROJECT_GAME_H
