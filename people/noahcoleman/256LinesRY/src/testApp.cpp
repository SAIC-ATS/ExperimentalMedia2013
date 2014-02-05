#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofDisableAntiAliasing();
    ofBackground(255,255,0);
    xPos = 0;
    yPos = 0;
  
    
    
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
//Manual Lines--No Distortion
//    ofLine(0, 0, 0, ofGetScreenHeight()); 
//    ofLine(2, 0, 2, ofGetScreenHeight());
//    ofLine(4, 0, 4, ofGetScreenHeight());
//    ofLine(6, 0, 6, ofGetScreenHeight());
//    ofLine(8, 0, 8, ofGetScreenHeight());

    
//For Loop--This is where i'm having problems
    
    ofDisableAntiAliasing();
    for (xPos = 0; xPos < 256; xPos++) {
        cout << ofGetWindowWidth() << endl;
        if (xPos%2 == 0) {
                        ofSetColor(255, 0, 0);
                        ofFill();
            ofLine(xPos*2, yPos, xPos*2, 500);  //make red line
            //cout << "xPos in modulo loop is " << xPos << endl;
            
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
