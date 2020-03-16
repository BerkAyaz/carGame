//
// Created by berka on 11/08/2019.
//

#ifndef CARGAME_SDLENEMY_H
#define CARGAME_SDLENEMY_H

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "../Enemy.h"
#include "SDLEnemy.h"
#include "SDLFact.h"

class SDLEnemy: public Enemy {
public:
    SDLEnemy(SDL_Renderer *gRenderer, SDL_Texture *gTexture);
    ~SDLEnemy();

    void Vis();

private:
    SDL_Renderer* m_renderer;
    SDL_Rect m_dimension;
    SDL_Texture* m_enemyTexture;

};


#endif //CARGAME_SDLENEMY_H
