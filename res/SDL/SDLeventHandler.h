//
// Created by berka on 28/07/2019.
//

#ifndef CARGAME_SDLEVENTHANDLER_H
#define CARGAME_SDLEVENTHANDLER_H

#include <SDL2/SDL.h>
#include "../eventHandler.h"


class SDLeventHandler: public eventHandler {
public:
    SDLeventHandler();
    ~SDLeventHandler();
    void handleEvent();
private:
};


#endif //CARGAME_SDLEVENTHANDLER_H
