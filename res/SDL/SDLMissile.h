//
// Created by berka on 11/08/2019.
//

#ifndef CARGAME_SDLMISSILE_H
#define CARGAME_SDLMISSILE_H

#include "SDL2/SDL.h"
#include "../Missile.h"


class SDLMissile: public Missile {
public:
    SDLMissile(SDL_Renderer* renderer, SDL_Texture* gTexture, int x, int y, std::string direction);
    ~SDLMissile();

    void Vis();

private:
    SDL_Renderer* m_renderer;
    SDL_Rect m_dimension;
    SDL_Texture* m_missileTexture;
};


#endif //CARGAME_SDLMISSILE_H
