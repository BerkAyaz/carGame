//
// Created by berka on 11/08/2019.
//

#include <iostream>
#include "SDLMissile.h"

using namespace std;

SDLMissile::SDLMissile(SDL_Renderer* renderer, SDL_Texture* gTexture, int x, int y, std::string direction) : Missile(x, y, direction){

    m_missileTexture = gTexture;
    m_renderer = renderer;

    m_dimension.w = m_width;
    m_dimension.h = m_height;
    m_dimension.x = m_xPos;
    m_dimension.y = m_yPos;

    m_missileDirection = direction;

}

SDLMissile::~SDLMissile() {

    if( m_missileTexture != NULL )
    {
        SDL_DestroyTexture( m_missileTexture );
        m_missileTexture = NULL;
        m_dimension = {0, 0, 0, 0};
    }
}

void SDLMissile::Vis() {
    m_dimension.x = m_xPos;
    m_dimension.y = m_yPos;
    SDL_RenderCopy( m_renderer, m_missileTexture, NULL, &m_dimension);
}