#include <iostream>
#include "res/SDL/SDLFact.h"
#include "res/SDL/SDLeventHandler.h"

Game* Game::m_instance=0;

int main( int argc, char *argv[] ){


    AFact* a = new SDLFact();
    eventHandler* eH = new SDLeventHandler();
    Game* G = Game::getInstance(a, eH);
    G -> start();

    delete a;
    delete eH;
    delete G;

    return 0;
}