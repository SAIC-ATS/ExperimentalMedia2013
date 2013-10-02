#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofDisableAntiAliasing();
    ofBackground(255);
    xPos = 0;
    yPos = 0;
    gradColor = 0;
    
    
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
ofDisableAntiAliasing();

    if (switchViews) {
    for (xPos = 0; xPos < 256; xPos++) {
            ofSetColor((xPos-255)*-1);
            ofFill();
            ofLine(xPos*2, yPos, xPos*2, ofGetWindowHeight());
            }
    }
    else {
        for (xPos = 0; xPos < 256; xPos++) {
            if (xPos%2==0) {
            ofSetColor(255,255,0);
            ofFill();
            ofLine(xPos*2, yPos, xPos*2, ofGetWindowHeight());
            }
            else {
            ofSetColor(255,0,0);
            ofFill();
            ofLine(xPos*2, yPos, xPos*2, ofGetWindowHeight());
            }
        }
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
    if (button==0) {
        i++;
    }
    if ((i%2)==0) {
        switchViews = true;
    }
    else {
        switchViews = false;
    }
    cout << i << endl;
    
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
