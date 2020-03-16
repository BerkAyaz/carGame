//
// Created by berka on 11/08/2019.
//

#include "Enemy.h"
#include "Game.h"
#include <ctime>

using namespace game;

Enemy::Enemy() {
    m_width = 75;
    m_height = 150;
    setSpawn();
    m_yPos = -(2 * m_height);
    m_lastShoot = std::clock();
}

Enemy::~Enemy() {

}

void Enemy::move() {
    m_yPos += m_speed;  //Enemies only can move downwards
}

void Enemy::setSpawn() {
    srand(time(0));
    int spawnPoint = (rand() % 4) + 1;  //Randomly pick one of the 4 spawn points
    switch (spawnPoint) {
        case 1:
            m_xPos = 25;
            break;
        case 2:
            m_xPos = SCREEN_WIDTH / 4 + 25;
            break;
        case 3:
            m_xPos = SCREEN_WIDTH / 2 + 25;
            break;
        case 4:
            m_xPos = SCREEN_WIDTH * 3 / 4 + 25;
            break;
    }
}

void Enemy::reload() {
    m_currentShoot = std::clock();
    if(m_currentShoot > m_lastShoot + m_reloadTime){
        m_canShoot = true;
        m_lastShoot = m_currentShoot;
    }
}