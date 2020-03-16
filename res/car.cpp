//
// Created by berka on 11/03/2019.
//

#include <iostream>
#include "car.h"
#include "Game.h"

using namespace game;

Car::Car(){
    m_width = 75;
    m_height = 150;
    m_xPos = SCREEN_WIDTH / 4 + 32;
    m_yPos = SCREEN_HEIGHT - m_height - 20;
}

void Car::move(std::string direction) {
    ////Move only when you are in the screen bounds////
    if((direction == "Up") || ( m_yPos + m_height > SCREEN_HEIGHT)){m_yPos -= m_speed;}
    if((direction == "Down") || (m_yPos < 0)){m_yPos += m_speed;}
    if((direction == "Left") || (m_xPos < 0)){m_xPos += m_speed;}
    if((direction == "Right") || (m_xPos + m_width > SCREEN_WIDTH)){m_xPos -= m_speed;}
}