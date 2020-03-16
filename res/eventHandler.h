//
// Created by berka on 28/07/2019.
//

#ifndef CARGAME_EVENTHANDLER_H
#define CARGAME_EVENTHANDLER_H


class eventHandler {
public:
    virtual void handleEvent()=0;

    bool isMoveLeft() const;

    bool isMoveRight() const;

    bool isMoveUp() const;

    bool isMoveDown() const;

    bool isShoot() const;

    bool m_isRunning = true;
    bool m_moveLeft = false, m_moveRight = false, m_moveUp = false, m_moveDown = false, m_shoot = false;
private:

};


#endif //CARGAME_EVENTHANDLER_H
