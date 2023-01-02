#include "PausedState.h"

PausedState::PausedState(){     
        pauseimage.load("images/ui/pause.png");
    }

void PausedState::update(){
}

void PausedState::draw(){
    pauseimage.draw(0,0,ofGetWidth(), ofGetHeight());
    
}

void PausedState::keyPressed(int key){
    if(key == OF_KEY_ESC){
        setFinished(true);
    }

}

void PausedState::reset(){
    setFinished(false);
}