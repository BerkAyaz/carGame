//
// Created by berka on 26/05/2019.
//

#ifndef PROJECT_ENTITIY_H
#define PROJECT_ENTITIY_H


class Entity {

public:
    virtual void Vis() = 0;

    int m_xPos, m_yPos, m_height, m_width;

};


#endif //PROJECT_ENTITIY_H
