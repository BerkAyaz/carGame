//
// Created by berka on 11/03/2019.
//

#ifndef GPPROJECT_SDLCAR_H
#define GPPROJECT_SDLCAR_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../car.h"
#include "SDLFact.h"

class SDLcar: public Car {

public:

    SDLcar(SDL_Renderer *renderer, SDL_Texture *gTexture);
    ~SDLcar();

    void setCartexture(std::string path);

    void Vis();

private:
    SDL_Renderer* m_renderer;
    SDL_Rect m_dimension;
    SDL_Texture* m_carTexture;
};


#endif //GPPROJECT_SDLCAR_H
