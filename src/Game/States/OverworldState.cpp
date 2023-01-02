#include "OverworldState.h"

OverworldState::OverworldState(Player *player, Area *area) {
    this->player = player;   
    camera = new OverworldCamera(player);
    loadArea(area);
}

void OverworldState::loadArea(Area *area) {
    this->area = area;
    overworldImage = area->getImage();
    music = area->getMusic();
    music.setVolume(0.25);
    music.setLoop(true);
    player->setOX(area->getEntrancePos().x);
    player->setOY(area->getEntrancePos().y);
}

void OverworldState::update() {
        player->inOverworldUpdate();      
    for (unsigned int i = 0; i < area->getEnemies().size(); i++) {
        if (!area->getEnemies().at(i)->isDead()) {
            area->getEnemies().at(i)->inOverworldUpdate();
            if (player->collides(area->getEnemies().at(i))) {
                setEnemy(area->getEnemies().at(i));
                setNextState("Battle");
                setFinished(true);
                break;
            }
        }
    }


    camera->update();
}

void OverworldState::draw() {
    overworldImage.drawSubsection(0, 0, camera->getDimensionX(), camera->getDimensionY(), camera->getLeftCornerX(), camera->getTopCornerY());
    player->inOverworldDraw();

    for (unsigned int i = 0; i < area->getEnemies().size(); i++) {
        if (!area->getEnemies().at(i)->isDead()) {
            int playerDistanceX = area->getEnemies().at(i)->getOX() - camera->getPlayerX();
            int playerDistanceY = area->getEnemies().at(i)->getOY() - camera->getPlayerY();
            area->getEnemies().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
            area->getEnemies().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
            area->getEnemies().at(i)->inOverworldDraw();
        }
    }

    for (unsigned int i = 0; i < area->getTerrain().size(); i++) {
            int playerDistanceX = area->getTerrain().at(i)->getOX() - camera->getPlayerX();
            int playerDistanceY = area->getTerrain().at(i)->getOY() - camera->getPlayerY();
            area->getTerrain().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
            area->getTerrain().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
            area->getTerrain().at(i)->inOverworldDraw();
        }
    
    for (unsigned int i = 0; i < area->getFriend().size(); i++) {
        if(!area->getFriend().at(i)->isDead()){
            int playerDistanceX = area->getFriend().at(i)->getOX() - camera->getPlayerX();
            int playerDistanceY = area->getFriend().at(i)->getOY() - camera->getPlayerY();
            area->getFriend().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
            area->getFriend().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
            area->getFriend().at(i)->inOverworldDraw();
        }
            
        }


    //Displays health bar
    ofNoFill();
    ofDrawRectRounded(40, 80, 100, 10, 10);
    
    ofFill();
    if(player->getHealth() <= 66 && player->getHealth() >= 34){
        ofSetColor(204,204,0);
    }else if(player->getHealth() <= 33){
        ofSetColor(204,0,0);
    }else{
        ofSetColor(0,204,0);
    }
    ofDrawRectRounded(40,80, player->getHealth(), 10, 10);

    //displays HP number
    ofSetColor(0,0,0);
    ofDrawBitmapString("HP:" + ofToString(round(player->getHealth())), 40, 70 );

    //displays area name 
    ofSetColor(0,0,0);
    ofDrawBitmapString("Area:" + area->getName(), 40, 50);

    //displays the number of enimies remaining
    ofSetColor(0,0,0);
    ofDrawBitmapString("Enemies Remaining:" + ofToString(area->getRemainingEnemies()), 400, 50); 

    ofSetColor(255, 255, 255);
}

void OverworldState::keyPressed(int key) {     
    player->keyPressed(key);

    //respawn all enemies
    if(key == 'r' || key == 'R'){
        area->resetEnemies();
    }

    //kill all enemies
     if(key == 'k' || key == 'K'){
         area->KillAll();
     }

     if(key == OF_KEY_ESC){
        setNextState("pause");
        setFinished(true);
        return;
     }

}

void OverworldState::keyReleased(int key) {
    player->keyReleased(key);
}

void OverworldState::reset() {
    player->keyReleased('w');
    player->keyReleased('a');
    player->keyReleased('s');
    player->keyReleased('d');
    setFinished(false);
    setNextState("");
}