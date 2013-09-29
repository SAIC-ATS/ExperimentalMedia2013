#include "testApp.h"


const int numberOfPoints = 50;
int xPos[numberOfPoints];
int yPos[numberOfPoints];

/*
 1. make two arrays of 50 random x and y positions
 2. place a dot on each x and y
 3. draw a line between 1 point and all 49 others, cycle it trough all 50
 
 */



//--------------------------------------------------------------
void testApp::setup(){
    
    ofBackground(0);
    
    for (int i = 0; i < numberOfPoints; i++) {
        
    xPos[i] = int(ofRandom(ofGetWidth()));
    yPos[i] = int(ofRandom(ofGetHeight()));
    }

}


//--------------------------------------------------------------
void testApp::draw(){

 
    for (int i = 0; i < numberOfPoints; i++) {        
        
        ofFill();
        ofSetColor(255, 0, 255);
        ofCircle(xPos[i], yPos[i], 5);
        
        for (int n = 1; i != n, n < numberOfPoints ; n++) {
            ofSetColor(0, 255, 255);
            ofLine(xPos[i], yPos[i], xPos[n], yPos[n]);
        }
    }
    
    
    if(newDrawing) {
        for (int i = 0; i < numberOfPoints; i++) {
            
            xPos[i] = int(ofRandom(ofGetWidth()));
            yPos[i] = int(ofRandom(ofGetHeight()));
        }
        newDrawing = false;
    }
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if(key == ' ') {
        newDrawing = true;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}


