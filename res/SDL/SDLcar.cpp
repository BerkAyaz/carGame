//
// Created by berka on 11/03/2019.
//
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDLcar.h"
#include "SDLFact.h"

SDLcar::SDLcar(SDL_Renderer* renderer, SDL_Texture* gTexture){

    m_carTexture = gTexture;
    m_renderer = renderer;

    m_dimension.w = m_width;
    m_dimension.h = m_height;
    m_dimension.x = m_xPos;
    m_dimension.y = m_yPos;

}

SDLcar::~SDLcar(){
    if( m_carTexture != NULL )
    {
        SDL_DestroyTexture( m_carTexture );
        m_carTexture = NULL;
        m_dimension = {0, 0, 0, 0};
    }
}

void SDLcar::setCartexture(std::string path) {
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        m_carTexture = SDL_CreateTextureFromSurface( m_renderer, loadedSurface );
        if( m_carTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
}

void SDLcar::Vis() {
    m_dimension.x = m_xPos;
    m_dimension.y = m_yPos;
    SDL_RenderCopy( m_renderer, m_carTexture, NULL, &m_dimension);
}