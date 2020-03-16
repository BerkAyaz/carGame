//
// Created by berka on 23/08/2019.
//

#include "SDLBonus.h"

SDLBonus::SDLBonus(SDL_Renderer* renderer, SDL_Texture* gTexture, std::string type){

    m_bonusTexture = gTexture;
    m_renderer = renderer;

    m_type = type;

    m_dimension.w = m_width;
    m_dimension.h = m_height;
    m_dimension.x = m_xPos;
    m_dimension.y = m_yPos;

}

SDLBonus::~SDLBonus(){
    if( m_bonusTexture != NULL )
    {
        SDL_DestroyTexture( m_bonusTexture );
        m_bonusTexture = NULL;
        m_dimension = {0, 0, 0, 0};
    }
}

void SDLBonus::Vis() {
    m_dimension.x = m_xPos;
    m_dimension.y = m_yPos;
    SDL_RenderCopy( m_renderer, m_bonusTexture, NULL, &m_dimension);
}