#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    glEnable(GL_DEPTH_TEST);
    yMin = 10;
    yMax = 758;
    space = 257;
    
   

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
   // 4 Draw a block of 256 vertical lines right next to each other using a for loop
    ofSetColor(255);
    for (int i = 0; i < 257; i++){
    ofLine(i,yMin,i, yMax);
    }
    
   // Make all of the odd lines red and all of even lines yellow. (hint: use and if statement and the modulo operator %)
    for (int i = 0; i < 257; i++){
        if (i % 2 == 0) {
        ofSetColor(255,255,51);
        }
        else if (i % 2 ==1){
        ofSetColor(255,0,0);
        }
        ofLine(i + space,yMin,i +space, yMax);
    }
    
    // change lines to form gradient
    for (int i = 0; i < 257; i++){
        ofSetColor(255-i);
        ofLine(i + space*2,yMin,i+space*2, yMax);
    }
    
    
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
