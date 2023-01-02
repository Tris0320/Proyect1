#include "Terrain.h"

Terrain::Terrain(int ox, int oy, string id, string name) : Entity(ox, oy, 50, 64) {
    this->id=  id;
    this->TerrainName = name;
    ofImage sprite;

    //sprite.crop(64, 500, 212, 177);
    
    sprite.load("images/entities/static/terrain.png");
    overworldSprite = sprite;


}

void Terrain::inOverworldUpdate() {}

void Terrain::inOverworldDraw() {
    overworldSprite.draw(renderX, renderY, ow, oh);
}

void Terrain::reset() {

}

Terrain::~Terrain() {
    
}