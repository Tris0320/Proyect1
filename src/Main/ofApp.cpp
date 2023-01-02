#include "ofApp.h"
#include "Area.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetEscapeQuitsApp(false);
    ofSetFrameRate(30);
    ofSetWindowTitle("Spooky Quest");
    initAreas();
    // Declaration and Initialization of States
    player = new Player(100, 6);
    titleState = new TitleState();
    overworldState = new OverworldState(player, currentArea);
    battleState = new BattleState(player, currentArea);    
    winState = new WinState();
    endGameState = new EndGameState();

    pausedState = new PausedState();
    // Initial State
    currentState = titleState;
}

//--------------------------------------------------------------
void ofApp::initAreas() {
    /**
     * @brief
     * each area is 672 pixels wide and 640 pixels high,
     * with 10 and 8 pixels of space between the player and the edge of the map respectively
     * each in-game pixel is 4 * 1 screen pixel
     */

    vector<Enemy *> enemies3;
    vector<Terrain *> terrains3;
    vector<Friend *> friend3;
    ofPoint entrancePosition3(4 * 110, 4 * 116);
    Enemy *area3Enemy1 = new Enemy("21", 30, 6, "enemy2", 4 * 120, 4 * 342);
    Enemy *area3Enemy2 = new Enemy("22", 30, 6, "enemy2", 4 * 254, 4 * 130);
    Enemy *area3Enemy3 = new Enemy("23", 30, 6, "enemy2", 4 * 542, 4 * 124);
    Enemy *area3Enemy4 = new Enemy("24", 30, 6, "enemy2", 4 * 532, 4 * 368);
    Enemy *area3Enemy5 = new Enemy("25", 30, 6, "enemy2", 4 * 266, 4 * 312);
    Enemy *area3Enemy6 = new Enemy("26", 30, 6, "enemy2", 4 * 194, 4 * 532);
    Terrain *area3Terrain1 = new Terrain(4 * 410, 4 * 180, "3", "rock");
    Friend *area3Friend1 = new Friend("1", "Friend", 4 * 135, 4 * 116);
    terrains3.push_back(area3Terrain1);
    enemies3.push_back(area3Enemy1);
    enemies3.push_back(area3Enemy2);
    enemies3.push_back(area3Enemy3);
    enemies3.push_back(area3Enemy4);
    enemies3.push_back(area3Enemy5);
    enemies3.push_back(area3Enemy6);
    friend3.push_back(area3Friend1);
    area3 = new Area("Ice Cave", NULL, "images/areas/area3.png", "audio/ice.wav", "images/stages/stage3.png", entrancePosition3, enemies3, terrains3, friend3);

     vector<Enemy *> enemies2;
     vector<Terrain *> terrains2;
     vector<Friend *> friend2;
    ofPoint entrancePosition2(4 * 130, 4 * 150);
    Enemy *area2Enemy1 = new Enemy("21", 30, 6, "enemy2", 4 * 120, 4 * 342);
    Enemy *area2Enemy2 = new Enemy("22", 30, 6, "enemy2", 4 * 254, 4 * 130);
    Enemy *area2Enemy3 = new Enemy("23", 30, 6, "enemy2", 4 * 542, 4 * 124);
    Enemy *area2Enemy4 = new Enemy("24", 30, 6, "enemy2", 4 * 532, 4 * 368);
    Enemy *area2Enemy5 = new Enemy("25", 30, 6, "enemy2", 4 * 266, 4 * 312);
    Terrain *area2Terrain1 = new Terrain(4 * 410, 4 * 180, "2", "rock");
    Friend *area2Friend1 = new Friend("1", "Friend", 4 * 155, 4 * 150);
    friend2.push_back(area2Friend1);
    terrains2.push_back(area2Terrain1);
    enemies2.push_back(area2Enemy1);
    enemies2.push_back(area2Enemy2);
    enemies2.push_back(area2Enemy3);
    enemies2.push_back(area2Enemy4);
    enemies2.push_back(area2Enemy5);
    area2 = new Area("Desert", area3, "images/areas/area2.png", "audio/desert.wav", "images/stages/stage2.png", entrancePosition2, enemies2, terrains2, friend2);

    vector<Enemy *> enemies1;
    vector<Terrain *> terrains1;
    vector<Friend *> friend1;
    ofPoint entrancePosition1(4 * 414, 4 * 566);
    Enemy *area1Enemy1 = new Enemy("11", 20, 4, "enemy1", 4 * 480, 4 * 432);
    Enemy *area1Enemy2 = new Enemy("12", 20, 4, "enemy1", 4 * 225, 4 * 178);
    Enemy *area1Enemy3 = new Enemy("13", 20, 4, "enemy1", 4 * 420, 4 * 178);
    Terrain *area1Terrain1 = new Terrain(4 * 400, 4 * 550, "11", "rock1");
    Terrain *area1Terrain2 = new Terrain(4 * 250, 4 * 160, "12", "rock1");
    Terrain *area1Terrain3 = new Terrain(4 * 600, 4 * 420, "13", "rock1");
    Friend *area1Friend1 = new Friend("1", "Friend", 4 * 440, 4 * 566);
    terrains1.push_back(area1Terrain1);
    terrains1.push_back(area1Terrain2);
    terrains1.push_back(area1Terrain3);
    enemies1.push_back(area1Enemy1);
    enemies1.push_back(area1Enemy2);
    enemies1.push_back(area1Enemy3);
    friend1.push_back(area1Friend1);
    area1 = new Area("Spooky Forest", area2, "images/areas/area1.png", "audio/forest.wav", "images/stages/stage1.png", entrancePosition1, enemies1, terrains1, friend1);
    currentArea = area1;
}

//--------------------------------------------------------------
void ofApp::update() {
    currentState->update();
    if (currentState->hasFinished()) {
        currentState->toggleMusic();
        if (currentState->getNextState() == "Title") {
            endGameState->setWin(false);
            area1->resetEnemies();
            area2->resetEnemies();
            area3->resetEnemies();
            currentArea = area1;
            battleState->reset();
            battleState->setStage(currentArea->getStage());
            overworldState->loadArea(currentArea);
            currentState = titleState;
        } else if (currentState->getNextState() == "Overworld") {
            currentState = overworldState;
        } else if (currentState->getNextState() == "Battle") {
            battleState->startBattle(overworldState->getEnemy());
            currentState = battleState;
        } else if (currentState->getNextState() == "Win") {
            overworldState->getEnemy()->kill();
            if (currentArea->getRemainingEnemies() == 0) {
                if (currentArea->getNextArea() == NULL) {
                    endGameState->setWin(true);
                    currentState = endGameState;
                } else {
                    currentArea = currentArea->getNextArea();
                    overworldState->loadArea(currentArea);
                    battleState->setStage(currentArea->getStage());
                    currentState = winState;
                }
            } else {
                currentState = winState;
            }

        } else if (currentState->getNextState() == "End"){
            currentState = endGameState;
            player->reset();

        } else if (currentState->getNextState() == "pause"){
            if(currentState == overworldState)
                pausedState->setNextState("Overworld");

            if(currentState == battleState)
                pausedState->setNextState("Battle");

            currentState = pausedState;

        }
        currentState->toggleMusic();
        currentState->reset();


    }

    if(currentArea == area2){
        player->setHealth(player->getHealth() - 0.05);
    }



}
//--------------------------------------------------------------
void ofApp::draw() {
    currentState->draw();


    //Adds a night time effect to area1 and area3
    if(currentState == overworldState){
        if(currentArea == area1){
            ofSetColor(100,100,100);
        }else if(currentArea == area3){
            ofSetColor(165,165,165);
        }   
    }else  if(currentState == titleState){
        ofSetColor(255,255,255);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

     currentState->keyPressed(key);

    //debug key to skip through areas
    if(key == 'n' || key == 'N'){
            currentState->toggleMusic();
            if (currentArea->getNextArea() == NULL) {
                    endGameState->setWin(true);
                    currentState = endGameState;
                } else {
                    currentArea = currentArea->getNextArea();
                    overworldState->loadArea(currentArea);
                    battleState->setStage(currentArea->getStage());
                    currentState = winState;
                }
         if (currentState->getNextState() == "End"){
            currentState = endGameState;
            player->reset();
        }
        currentState->toggleMusic();
        currentState->reset();
    }
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
    currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
    currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    currentState->dragEvent(dragInfo);
}