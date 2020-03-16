//
// Created by berka on 23/08/2019.
//

#include <cstdlib>
#include "Bonus.h"
#include "game.h"

using namespace game;

Bonus::Bonus() {
    m_xPos = rand() % SCREEN_WIDTH;
    m_yPos = -(2 * m_height);
    m_height = 48;
    m_width = 48;
}

void Bonus::move() {
    m_yPos += m_speed;  //Bonuses can only move downwards
}