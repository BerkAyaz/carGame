//
// Created by berka on 23/08/2019.
//

#ifndef CARGAME_SDLBONUS_H
#define CARGAME_SDLBONUS_H

#include "../Bonus.h"
#include "SDL2/SDL.h"
#include "string.h"
#include <string>

using namespace::std;

class SDLBonus: public Bonus {
public:
    SDLBonus(SDL_Renderer* renderer, SDL_Texture* gTexture, std::string type);
    ~SDLBonus();

    void Vis();
private:
    SDL_Renderer* m_renderer;
    SDL_Rect m_dimension;
    SDL_Texture* m_bonusTexture;
};


#endif //CARGAME_SDLBONUS_H
