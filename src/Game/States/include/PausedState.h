#pragma once

#include "Area.h"
#include "Enemy.h"
#include "Player.h"
#include "State.h"

class PausedState : public State {
private:     
    ofImage pauseimage;

public:
    PausedState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
};
