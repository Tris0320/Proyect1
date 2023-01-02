#include "Fighter.h"

Fighter::Fighter(int fx, int fy, int fw, int fh, double health, int baseDamage) {
    this->fx = fx;
    this->fy = fy;
    this->fh = fh;
    this->fw = fw;
    this->health = health;
    this->baseDamage = baseDamage;
}

Fighter::~Fighter(){}

void Fighter::fightingDraw() {
    fightingSprite.draw(fx, fy, fw, fh);
}