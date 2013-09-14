#include "testApp.h"
float xPos;
float yPos;


//--------------------------------------------------------------
void testApp::setup(){
    ofEnableSmoothing();
    ofSetFrameRate(30);
  
    
}

//--------------------------------------------------------------
void testApp::update(){
    theBall.x += (mouseX - theBall.x)*0.1;
    theBall.y += (mouseY - theBall.y)*0.1;

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackgroundGradient(ofColor::gray,ofColor(30,10,30), OF_GRADIENT_CIRCULAR);
    theBall.draw();
    
    
    
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
    xPos = ofRandom(ofGetWindowWidth());
    yPos = ofRandom(ofGetWindowHeight());

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
