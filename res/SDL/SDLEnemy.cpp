//
// Created by berka on 11/08/2019.
//

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDLEnemy.h"

SDLEnemy::SDLEnemy(SDL_Renderer *gRenderer, SDL_Texture *gTexture) {
    m_renderer = gRenderer;
    m_enemyTexture = gTexture;

    m_dimension.w = m_width;
    m_dimension.h = m_height;
    m_dimension.x = m_xPos;
    m_dimension.y = m_yPos;
}

SDLEnemy::~SDLEnemy(){
    if( m_enemyTexture != NULL )
    {
        SDL_DestroyTexture( m_enemyTexture );
        m_enemyTexture = NULL;
        m_dimension = {0, 0, 0, 0};
    }
}

void SDLEnemy::Vis() {
    m_dimension.x = m_xPos;
    m_dimension.y = m_yPos;
    SDL_RenderCopy( m_renderer, m_enemyTexture, NULL, &m_dimension);
}