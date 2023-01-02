#pragma once

#include "Enemy.h"
#include "OverworldCamera.h"
#include "Player.h"
#include "Terrain.h"
#include "Friend.h"

class Area {
   private:
    string name;
    ofImage areaImage;
    ofSoundPlayer areaMusic;
    ofImage areaStage;
    ofPoint entrancePosition;
    std::vector<Enemy *> enemies;
    std::vector<Terrain *> terrains;
    std::vector<Friend *> friends;
    Area *nextArea;

   public:
    Area(string name, Area *nextArea, string areaImagePath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Enemy *> enemies, vector<Terrain *> terrains, vector<Friend *> friends);
    void resetEnemies();
    void KillAll();
    string getName() { return name; }
    ofImage getImage() { return areaImage; }
    ofSoundPlayer getMusic() { return areaMusic; }
    ofImage getStage() { return areaStage; }
    ofPoint getEntrancePos() { return entrancePosition; }
    vector<Enemy *> getEnemies() { return enemies; }
    vector<Terrain *> getTerrain() { return terrains; }
    vector<Friend *> getFriend() { return friends; }
    int getRemainingEnemies();
    Area *getNextArea() { return nextArea; }
    void setName(string name) { this->name = name; }
    void setEnemies(std::vector<Enemy *> enemies) { this->enemies = enemies; }

};