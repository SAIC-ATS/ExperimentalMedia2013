#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    r = ofRandom(10);
    
    positionX.resize(50);
     positionY.resize(50);
    for(int i =0; i< positionX.size()+1;i++){
        positionX[i] =ofRandom(ofGetWidth());
        positionY[i] =ofRandom(ofGetHeight());

    }
    /*
    for (int i =0; i <50; i++){
        positionX[i] = ofRandom(ofGetWidth());
        positionY[i] = ofRandom(ofGetHeight());
    }
     */
}


//--------------------------------------------------------------
void testApp::draw(){

    ofBackground(0, 0, 0);
    ofFill();
    ofSetColor(255, 255, 255);
    for(int i = 0; i < positionX.size()+1 ; i++){
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
        ofCircle(positionX[i], positionY[i], r);
        ofLine(positionX[i], positionY[i], positionX[i+1], positionY[i+1]);
        
    }
  //  cout << positionX.size() << endl;
  
}


