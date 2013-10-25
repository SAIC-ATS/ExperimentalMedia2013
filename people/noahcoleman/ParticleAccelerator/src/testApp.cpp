#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    numBalls = 50;
   
        Ball redBall;
        
        redBall.position.x = ofRandom(ofGetWidth());
        redBall.position.y = ofRandom(ofGetHeight());
        
        redBall.velocity.x = ofRandom(-10, 10);
        redBall.velocity.y = 20;
        
        redBall.acceleration.y = 0.8;

}

//--------------------------------------------------------------
void testApp::update(){
    redBall.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    redBall.draw();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
