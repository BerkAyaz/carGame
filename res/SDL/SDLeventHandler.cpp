//
// Created by berka on 28/07/2019.
//

#include "SDLeventHandler.h"
#include "../eventHandler.h"
#include "SDL2/SDL.h"

SDLeventHandler::SDLeventHandler() {

}

SDLeventHandler::~SDLeventHandler() {

}

void SDLeventHandler::handleEvent() {

    SDL_Event e;
    SDL_PollEvent(&e);

    switch (e.type){
        case SDL_QUIT: m_isRunning = false;break;

        default:
            break;
    }

    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_z: m_moveUp = true; break;
            case SDLK_s: m_moveDown = true; break;
            case SDLK_q: m_moveRight = true; break;
            case SDLK_d: m_moveLeft = true; break;
            case SDLK_SPACE: m_shoot = true; break;

        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_z: m_moveUp = false; break;
            case SDLK_s: m_moveDown = false; break;
            case SDLK_q: m_moveRight = false; break;
            case SDLK_d: m_moveLeft = false; break;
            case SDLK_SPACE: m_shoot = false; break;

        }
    }

}
