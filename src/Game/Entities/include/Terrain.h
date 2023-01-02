#pragma once

#include "Entity.h"

class Terrain : public Entity {
    private:
    int renderX = 1000;
    int renderY = 1000;
    string id;
    string TerrainName;
    ofImage sprite;

    public:
    Terrain(int ox, int oy, string id, string name);
    ~Terrain();
    int getOX() { return ox; };
    int getOY() { return oy; };
    void setRenderX(int x) {renderX = x; };
    void setRenderY(int y) {renderY = y; };
    virtual void inOverworldUpdate();
    virtual void inOverworldDraw();
    void reset();
    string getId() { return id; };
    ofImage getSprite() { return overworldSprite; };

};