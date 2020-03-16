//
// Created by berka on 28/07/2019.
//

#include "eventHandler.h"

bool eventHandler::isMoveLeft() const {
    return m_moveLeft;
}

bool eventHandler::isMoveRight() const {
    return m_moveRight;
}

bool eventHandler::isMoveUp() const {
    return m_moveUp;
}

bool eventHandler::isMoveDown() const {
    return m_moveDown;
}

bool eventHandler::isShoot() const {
    return m_shoot;
}
