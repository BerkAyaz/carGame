//
// Created by berka on 11/03/2019.
//

#ifndef GPPROJECT_SDLFACT_H
#define GPPROJECT_SDLFACT_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../AFact.h"
#include "../Game.h"
#include <string>

using namespace::std;
using namespace game;

class SDLFact : public AFact {

public:
    //Loads individual image as texture
    SDL_Texture* loadTexture(std::string path );

    SDLFact();
    ~SDLFact();
    bool init();
    void loadAllTextures();
    void render();
    Car* createCar();
    Missile* createMissile(int x, int y);
    Missile* createEnemyMissile(int x, int y);
    Enemy* createEnemy();
    Bonus* createBonus(int type);

    void visLives(int x, int y);


    void updateBackground();

private:

    int m_scrollspeed = 10;
    int m_scrollingOffset = 0;

    //The window we'll be rendering to
    SDL_Window* m_gWindow = NULL;
    //The window renderer
    SDL_Renderer* m_gRenderer = NULL;

    SDL_Texture* m_BGTexture;

    SDL_Texture* m_carTexture;
    SDL_Texture* m_missileTexture;
    SDL_Texture* m_enemyTexture;
    SDL_Texture* m_enemyMissileTexture;
    SDL_Texture* m_livesTexture;
    SDL_Texture* m_bonusTexture;
    SDL_Texture* m_starTexture;
};


#endif //GPPROJECT_SDLFACT_H
