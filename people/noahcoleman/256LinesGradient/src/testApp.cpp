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
    
    for (xPos = 0; xPos < 256; xPos++) {
        //cout << ofGetWindowWidth() << endl;
       
            //cout <<gradColor<< endl;
            ofSetColor((xPos-255)*-1);
            ofFill();
            ofLine(xPos*2, yPos, xPos*2, 500);

            
        

        
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
