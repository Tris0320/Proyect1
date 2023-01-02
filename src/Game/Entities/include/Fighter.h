#pragma once

#include "ofMain.h"


class Fighter {
    protected:
    double health;
    int baseDamage;
    int fx, fy, fw, fh; // Fighting coordinates and dimensions
    ofImage fightingSprite;

    public:
    Fighter(int fx, int fy, int fw, int fh, double health, int baseDamage);
    virtual ~Fighter();
    virtual void fightingUpdate() = 0;
    virtual void fightingDraw();
    double getHealth() { return health; };
    void setHealth(double health) { this->health = health; };
    int getDmg() { return baseDamage; };
    void setDmg(int baseDamage) { this->baseDamage = baseDamage; };
};