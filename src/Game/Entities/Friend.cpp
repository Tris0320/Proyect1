#include "Friend.h"

Friend::Friend(string id, string entityName, int ox, int oy) : Entity(ox, oy, 50, 64) {
    this->id = id;
    this->entityName = entityName;
    moveTimer = 60;
    vector<ofImage> downFrames;
    vector<ofImage> upFrames;
    vector<ofImage> leftFrames;
    vector<ofImage> rightFrames;
    ofImage sprite;
    ofImage temp;

    sprite.load("images/entities/enemy/sprite.png");
    

    int w = 48, h = 48;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            temp.cropFrom(sprite, 6 + w * i, 192 + h * j, w - 12, h);
            if (j == 0)
                downFrames.push_back(temp);
            else if (j == 1)
                leftFrames.push_back(temp);
            else if (j == 2)
                rightFrames.push_back(temp);
            else
                upFrames.push_back(temp);
        }   
    }
    walkDown = new Animation(3, downFrames);
    walkUp = new Animation(3, upFrames);
    walkLeft = new Animation(3, leftFrames);
    walkRight = new Animation(3, rightFrames);
    

    direction = Direction::down;
}

void Friend::inOverworldUpdate() {
    if (moveTimer == 60) {
        walking = true;
        switch (direction) {
           
            case Direction::right:
                direction = Direction::down;
                break;
            case Direction::left:
                direction = Direction::right;
                break;
            case Direction::down:
                direction = Direction::left;
                break;
                default:
                direction = Direction::right;
                break;
        }
    }
    if (moveTimer == 45) {
        walking = false;
    }
    moveTimer--;
    if (moveTimer == 0) moveTimer = 60;

    if (walking) {
        switch (direction) {
            case Direction::left:
                this->ox -= speed;
                walkLeft->update();
                overworldSprite = walkLeft->getCurrentFrame();
                break;
            case Direction::right:
                this->ox += speed/2;
                this->oy -= speed;
                walkRight->update();
                overworldSprite = walkRight->getCurrentFrame();
                break;
            case Direction::down:
                this->oy += speed;
                this->ox += speed/2;
                walkDown->update();
                overworldSprite = walkDown->getCurrentFrame();
                break;
                default:
                break;
        }
    } else {
        switch (direction) {
            case Direction::left:
                overworldSprite = walkLeft->getCurrentFrame();
                break;
            case Direction::right:
                overworldSprite = walkRight->getCurrentFrame();
                break;
           
            case Direction::down:
                overworldSprite = walkDown->getCurrentFrame();
                break;
                default:
                break;
        }
    }
}

void Friend::inOverworldDraw() {    
    overworldSprite.draw(renderX, renderY, ow, oh);
}

void Friend::reset() {
}

Friend::~Friend() {
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}
