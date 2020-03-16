//
// Created by berka on 11/03/2019.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <thread>
#include "Game.h"

using namespace game;

Game::Game(AFact* aFactory, eventHandler* eH){
    m_aFactory = aFactory;
    m_eventHandler = eH;

    loadConfig();
}

Game::~Game() {
    delete m_car;
    m_missiles.clear();
    m_enemies.clear();
    m_enemyMissiles.clear();
    m_bonusses.clear();
    delete m_eventHandler;
    delete m_aFactory;
}

void Game::start(){
    ////FPS REGELING/////////////////////
    const int fpsrate = 60;
    using clock = std::chrono::steady_clock;
    auto next_frame = clock::now();
    //////SPAWN REGELING///////////////////;
    int lastSpawn, currentSpawn;
    lastSpawn = std::clock();
    //////RELOAD REGELING//////////////////
    int currentReload, lastReload;
    lastReload = std::clock();
    //////BONUS REGELING//////////////////
    int lastBonus, currentBonus;
    lastBonus = std::clock();
    //////INVINCIBLE REGELING//////////////////
    int lastInvincible, currentInvincible;
    lastInvincible = std::clock();

    /////////////////////////////////////
    m_car = m_aFactory -> createCar();
    m_car->setCartexture(m_carSkin);

    while(m_eventHandler->m_isRunning){

        next_frame += std::chrono::milliseconds(1000 / fpsrate); // 60 FPS
        handleEvent();
        ///////////////HANDLE KEYBOARD INPUTS//////////
        if(m_eventHandler->isMoveUp()){m_car->move("Up");}
        if(m_eventHandler->isMoveDown()){m_car->move("Down");}
        if(m_eventHandler->isMoveLeft()){m_car->move("Left");}
        if(m_eventHandler->isMoveRight()){m_car->move("Right");}
        if(m_eventHandler->isShoot()){
            if((m_car->m_currentAmmoSize > 0)){
                addMissile();
                m_car->m_currentAmmoSize--;
            }
            else{
                printf("Reloading...\n");
            }

        }

        m_aFactory->updateBackground();
        m_car->Vis();

        ////////////UPDATE ENEMIES///////////////////////////////
        for(std::list<Enemy *>::iterator it = m_enemies.begin(); it != m_enemies.end(); ++it) {
            Enemy *itEnemy = *it;
            itEnemy->move();
            itEnemy->Vis();
        }
        ////////////UPDATE THE MISSILES//////////////////////////
        for(std::list<Missile *>::iterator it = m_missiles.begin(); it != m_missiles.end(); ++it){
            Missile *itMissile = *it;
            itMissile->move();
            itMissile->Vis();
        }
        ////////////UPDATE THE MISSILES//////////////////////////
        for(std::list<Missile *>::iterator it = m_enemyMissiles.begin(); it != m_enemyMissiles.end(); ++it){
            Missile *itMissile = *it;
            itMissile->move();
            itMissile->Vis();
        }
        ////////////UPDATE BONUSSES///////////////////////////////
        for(std::list<Bonus *>::iterator it = m_bonusses.begin(); it != m_bonusses.end(); ++it) {
            Bonus *itBonus = *it;
            itBonus->move();
            itBonus->Vis();
        }
        //////////////UPDATE LIVES///////////////////////////////
        for(int i =0; i < m_car->m_lives; i++){
            m_aFactory->visLives(10 + i * 40, 10);
        }
        //////RENDER BUFFER////////
        renderGame();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////CHECK FOR MISSILE-ENEMY COLLISION/////////////
        for(std::list<Missile *>::iterator missileIt = m_missiles.begin(); missileIt != m_missiles.end(); ++missileIt) {
            for (std::list<Enemy *>::iterator enemyIt = m_enemies.begin(); enemyIt != m_enemies.end(); ++enemyIt) {
                Missile *itMissile = *missileIt;
                Enemy *itEnemy = *enemyIt;
                if(checkCollision(itMissile, itEnemy)){
                    m_enemies.erase(enemyIt);
                    m_missiles.erase(missileIt);
                    m_score += 100;
                    printf("Score: %d\n",m_score);
                }
            }
        }

        ///////////CHECK FOR MISSILE-ENEMY MISSILE COLLISION/////////////
        for(std::list<Missile *>::iterator missileIt = m_missiles.begin(); missileIt != m_missiles.end(); ++missileIt) {
            for (std::list<Missile *>::iterator enemyMissileIt = m_enemyMissiles.begin(); enemyMissileIt != m_enemyMissiles.end(); ++enemyMissileIt) {
                Missile *itMissile = *missileIt;
                Missile *itEnemyMissile = *enemyMissileIt;
                if(checkCollision(itMissile, itEnemyMissile)){
                    m_enemyMissiles.erase(enemyMissileIt);
                    m_missiles.erase(missileIt);
                }
            }
        }

        //////////CHECK FOR ENEMY MISSILE-PLAYER COLLISION/////////
        for(std::list<Missile *>::iterator missileIt = m_enemyMissiles.begin(); missileIt != m_enemyMissiles.end(); ++missileIt) {
            Missile *itMissile = *missileIt;
            if((checkCollision(itMissile, m_car)) && !m_invincible){
                m_enemyMissiles.erase(missileIt);
                m_car->m_lives--;
            }
            if(checkCollision(itMissile, m_car)){
                m_enemyMissiles.erase(missileIt);
            }
        }

        //////////CHECK FOR BONUS-PLAYER COLLISION/////////
        for(std::list<Bonus *>::iterator bonusIt = m_bonusses.begin(); bonusIt != m_bonusses.end(); ++bonusIt) {
            Bonus *itBonus = *bonusIt;
            if(checkCollision(itBonus, m_car)){
                if(itBonus->m_type == "puntenBonus"){
                    m_score += 1000;
                    printf("Score: %d\n",m_score);
                }
                if(itBonus->m_type == "Invincible"){
                    m_invincible = true;
                    m_car->setCartexture("../textures/invincibleCar.png");
                    printf("You are now invincible\n");
                    lastInvincible = std::clock();
                }
                m_bonusses.erase(bonusIt);
            }
        }

        ///////////SPAWN RANDOM ENEMIES/////////////
        currentSpawn = std::clock();
        if(currentSpawn > lastSpawn + m_maxSpawnTime){
            addEnemy();
            lastSpawn = currentSpawn;
        }

        ///////////SPAWN RANDOM BONUSES/////////////
        currentBonus = std::clock();
        if(currentBonus > lastBonus + m_maxBonusTime){
            addBonus();
            lastBonus = currentBonus;
        }

        ///////////MAKE ENEMIES SHOOT IF ABLE TO SHOOT AND PLAYER IS IN RANGE////////////////
        for (std::list<Enemy *>::iterator enemyIt = m_enemies.begin(); enemyIt != m_enemies.end(); ++enemyIt) {
            Enemy *itEnemy = *enemyIt;
            if(((m_car->m_xPos > itEnemy->m_xPos) && (m_car->m_xPos < (itEnemy->m_xPos + itEnemy->m_width)) ||
               ((m_car->m_xPos + m_car->m_width > itEnemy->m_xPos) && (m_car->m_xPos + m_car->m_width < (itEnemy->m_xPos + itEnemy->m_width)))) &&
               (itEnemy->m_canShoot)){
                itEnemy->m_canShoot = false;
                addEnemyMissile(itEnemy);
            }
        }

        /////////ENEMIES RELOAD////////////////////////
        for (std::list<Enemy *>::iterator enemyIt = m_enemies.begin(); enemyIt != m_enemies.end(); ++enemyIt) {
            Enemy *itEnemy = *enemyIt;
            if(!itEnemy->m_canShoot)
            itEnemy->reload();
        }

        //////////RELOAD IF NEEDED/////////////////////
        if(m_car->m_currentAmmoSize <= 0){
            currentReload = std::clock();
            if(currentReload > lastReload + m_maxReloadTime){
                printf("Clip reloaded!\n ");
                m_car->m_currentAmmoSize = m_car->m_maxAmmoSize;
                lastReload = currentReload;
            }
        }


        /////////////////////////////////////////////////////////////////////////////////////////
        ///////CHECK IF MISSILES ARE ON THE SCREEN IF NOT, DELETE/////
        for(std::list<Missile *>::iterator it = m_missiles.begin(); it != m_missiles.end(); ++it){
            Missile *itMissile = *it;
            if(itMissile->m_yPos < 0){
                m_missiles.erase(it);
            }
        }

        ///////CHECK IF ENEMIES ARE ON THE SCREEN IF NOT, DELETE/////
        for(std::list<Enemy *>::iterator it = m_enemies.begin(); it != m_enemies.end(); ++it){
            Enemy *itEnemy = *it;
            if(itEnemy->m_yPos > SCREEN_HEIGHT){
                m_enemies.erase(it);
            }
        }

        ///////CHECK IF BONUSES ARE ON THE SCREEN IF NOT, DELETE/////
        for(std::list<Bonus *>::iterator it = m_bonusses.begin(); it != m_bonusses.end(); ++it){
            Bonus *itBonus = *it;
            if(itBonus->m_yPos > SCREEN_HEIGHT){
                m_bonusses.erase(it);
            }
        }

        ///////CHECK IF ENEMY MISSILES ARE ON THE SCREEN IF NOT, DELETE/////
        for(std::list<Missile *>::iterator it = m_enemyMissiles.begin(); it != m_enemyMissiles.end(); ++it){
            Missile *itMissile = *it;
            if(itMissile->m_yPos > SCREEN_HEIGHT){
                m_enemyMissiles.erase(it);
            }
        }
        //////////////////////////////////////////////////////////////////////////////////////////////
        //////////////UPDATE INVINCIBLE//////////////////
        if(m_invincible == true){
            currentInvincible = std::clock();
            if(currentInvincible > lastInvincible + m_maxInvincibleTime){
                m_invincible = false;
                m_car->setCartexture(m_carSkin);
                printf("You are no longer invincible\n");
            }
        }

        //////////////UPDATE RUNNING//////////////////
        if(m_car->m_lives == 0){
            m_eventHandler->m_isRunning = false;
        }

        ////////DELAY OM FPS TE CAPPEN/////////////////
        std::this_thread::sleep_until(next_frame);
    }

    if(m_score > m_highScore){
        m_highScore = m_score;
    }

    //////GAME END/////////
    printf("\nYou died!\n");

    saveConfig();

    printf("\nFinal score: %d\n",m_score);
    printf("Highscore: %d\n",m_highScore);
}

void Game::addMissile() {
    m_missiles.push_back(m_aFactory->createMissile(m_car->m_xPos + m_car->m_width/4, m_car->m_yPos - m_car->m_height/8));
    m_eventHandler->m_shoot = false;
}

void Game::addEnemyMissile(Enemy *e){
    m_enemyMissiles.push_back(m_aFactory->createEnemyMissile(e->m_xPos + e->m_width/4, e->m_yPos + e->m_height/8));
}

void Game::addEnemy(){
    m_enemies.push_back(m_aFactory->createEnemy());
    m_enemyCount++;
}

void Game::addBonus(){
    int type = 1 + (rand() % 2);
    m_bonusses.push_back(m_aFactory->createBonus(type));
}

bool Game::checkCollision(Entity *a, Entity *b){
    if (a->m_xPos < b->m_xPos + b->m_width && a->m_xPos + a->m_width > b->m_xPos && a->m_yPos < b->m_yPos + b->m_height && a->m_yPos + a->m_height > b->m_yPos){
        return true;
    }
    return false;
}

void Game::renderGame() {
    m_aFactory->render();
}

void Game::handleEvent() {
    m_eventHandler -> handleEvent();
}

void Game::loadConfig() {
    std::ifstream configFile ("../config.txt");
    if (configFile.is_open())
    {
        std::string line;
        while(getline(configFile, line)){
            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
            auto delimiterPos = line.find("=");
            auto name = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 1);
            if(name == "Highscore"){
                m_highScore = std::stoi(value);
            }
            if(name == "carSkin"){
                m_carSkin = value;
            }
        }
        configFile.close();
    }
    else {
        std::cerr << "Couldn't open config file for reading.\n";
    }
}

void Game::saveConfig() {
    std::ofstream configFile ("../config.txt");
    if (configFile.is_open())
    {
        configFile << "Highscore = " <<m_highScore<<"\n";
        configFile << "carSkin = " <<m_carSkin<<"\n";
        configFile.close();
        printf("Data saved succesfully!\n");
    }
    else {
        std::cerr << "Couldn't open config file for writing.\n";
    }
}


//SINGLETON PATTERN
Game* Game::getInstance(AFact* aFactory, eventHandler* eH){
    if(m_instance == 0){
        m_instance = new Game(aFactory, eH );
    }
    return m_instance;
}