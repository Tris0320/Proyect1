#include "Enemy.h"

Enemy::Enemy(string id, double health, int baseDamage, string entityName, int ox, int oy) : Entity(ox, oy, 50, 64) , Fighter(420, 220, 97, 125, health, baseDamage) {
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
    fighting = new Animation(7, leftFrames);

    direction = Direction::down;
}

void Enemy::inOverworldUpdate() {
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
                overworldSprite = walkRight->getCurrentFrame();;
                break;
           
            case Direction::down:
                overworldSprite = walkDown->getCurrentFrame();
                break;
                default:
                break;
        }
    }
}

void Enemy::inOverworldDraw() {
    // uncomment these if you want the coordinates of the enemies in the current area
    // ofDrawBitmapString("rX:" + to_string(renderX), 100 + 125 * ((stoi(id) % 10) - 1), 100);
    // ofDrawBitmapString("rY:" + to_string(renderY), 100 + 125 * ((stoi(id) % 10) - 1), 120);
    // ofDrawBitmapString("ow:" + to_string(ox), 100 + 125 * ((stoi(id) % 10) - 1), 140);
    // ofDrawBitmapString("oy:" + to_string(oy), 100 + 125 * ((stoi(id) % 10) - 1), 160);
    overworldSprite.draw(renderX, renderY, ow, oh);
}

void Enemy::fightingUpdate() {
    fightingSprite = fighting->getCurrentFrame();
    fighting->update();
}

void Enemy::reset() {
}

Enemy::~Enemy() {
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
    delete fighting;
}