//
// Created by berka on 11/03/2019.
//

#include "SDLFact.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDLcar.h"
#include "../car.h"
#include "../Game.h"
#include "../Missile.h"
#include "SDLMissile.h"
#include "SDLEnemy.h"
#include "SDLBonus.h"

using namespace::std;
using namespace game;

SDLFact::SDLFact() {
    if (!init()) {
        cout << "Initialisatie mislukt" << endl;
    } else {
        cout << "Initialisatie compleet" << endl;
    }
    loadAllTextures();
}

SDLFact::~SDLFact() {
    //Free loaded images
    SDL_DestroyTexture(m_BGTexture);
    m_BGTexture = NULL;
    SDL_DestroyTexture(m_carTexture);
    m_carTexture = NULL;
    SDL_DestroyTexture(m_bonusTexture);
    m_bonusTexture = NULL;
    SDL_DestroyTexture(m_missileTexture);
    m_missileTexture = NULL;
    SDL_DestroyTexture(m_enemyMissileTexture);
    m_enemyMissileTexture = NULL;
    SDL_DestroyTexture(m_enemyTexture);
    m_enemyTexture = NULL;
    SDL_DestroyTexture(m_livesTexture);
    m_livesTexture = NULL;
    SDL_DestroyTexture(m_starTexture);
    m_starTexture = NULL;


    //Destroy window
    SDL_DestroyRenderer( m_gRenderer );
    SDL_DestroyWindow( m_gWindow );
    m_gWindow = NULL;
    m_gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

bool SDLFact::init(){

    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        m_gWindow = SDL_CreateWindow( "Need for Speed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( m_gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            m_gRenderer = SDL_CreateRenderer( m_gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( m_gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( m_gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                    if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    return success;
}

SDL_Texture* SDLFact::loadTexture( string path ){

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( m_gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

void SDLFact::loadAllTextures() {
    m_carTexture = loadTexture("../textures/yellowCar.png");
    m_missileTexture = loadTexture("../textures/missile.png");
    m_enemyTexture = loadTexture("../textures/redCar.png");
    m_enemyMissileTexture = loadTexture("../textures/eMissile.png");
    m_livesTexture = loadTexture("../textures/heart.gif");
    m_bonusTexture = loadTexture("../textures/coin.png");
    m_starTexture = loadTexture("../textures/star.png");
    m_BGTexture = loadTexture("../textures/road.png");
}

Car* SDLFact::createCar(){
    return new SDLcar(m_gRenderer, m_carTexture);
}

Missile* SDLFact::createMissile(int x, int y) {
    return new SDLMissile(m_gRenderer, m_missileTexture, x, y, "Up");
}

Enemy* SDLFact::createEnemy() {
    return new SDLEnemy(m_gRenderer, m_enemyTexture);
}

Missile* SDLFact::createEnemyMissile(int x, int y) {
    return new SDLMissile(m_gRenderer, m_enemyMissileTexture, x, y, "Down");
}

Bonus* SDLFact::createBonus(int type) {
    switch(type){
        case 1:     return new SDLBonus(m_gRenderer, m_bonusTexture, "puntenBonus");break;
        case 2:     return new SDLBonus(m_gRenderer, m_starTexture, "Invincible");break;
    }
}

void SDLFact::visLives(int x, int y) {
    SDL_Rect livesDimension = {x, y, 32, 32};
    SDL_RenderCopy( m_gRenderer, m_livesTexture, NULL, &livesDimension);
}

void SDLFact::updateBackground() {
    m_scrollingOffset = m_scrollingOffset + m_scrollspeed;
    if (m_scrollingOffset > SCREEN_HEIGHT) {
        m_scrollingOffset = 0;
    }
    SDL_Rect renderQuad = {0, m_scrollingOffset, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(m_gRenderer, m_BGTexture, NULL, &renderQuad);    //moving first piece of background to the buffer
    renderQuad = {0, m_scrollingOffset - (SCREEN_HEIGHT), SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(m_gRenderer, m_BGTexture, NULL, &renderQuad);    //moving the second background piece of the background to the buffer
}

void SDLFact::render() {
    //Render everything in the buffer to the screen
    SDL_RenderPresent(m_gRenderer);
    SDL_RenderClear(m_gRenderer);
}