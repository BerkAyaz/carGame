//
// Created by berka on 11/08/2019.
//

#include "Missile.h"


Missile::Missile(int x, int y, std::string direction) {
    m_height = 64;
    m_width = 32;
    m_xPos = x;
    m_yPos = y;

    m_missileDirection = direction;
}

Missile::~Missile() {}

void Missile::move() {
    if(m_missileDirection == "Up"){ //UP for player missiles
        m_yPos -= m_missileSpeed;
    }
    if(m_missileDirection == "Down"){ //DOWN for enemy missiles
        m_yPos += m_missileSpeed;
    }
}