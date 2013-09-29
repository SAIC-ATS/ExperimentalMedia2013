#include "testApp.h"

#define NUM_POINTS 25
#define NUM_POINTS2 25

float circleX [NUM_POINTS];
float circleY [NUM_POINTS];
float circleRad [NUM_POINTS];

float circleX2 [NUM_POINTS2];
float circleY2 [NUM_POINTS2];
float circleRad2 [NUM_POINTS2];


//draw fifty circle and connect connect connect 

//--------------------------------------------------------------
void testApp::setup(){
    
    for (int i = 0 ; i < NUM_POINTS; i ++)
    {
        circleX[i] = ofRandom(ofGetWidth());
        circleY[i] = ofRandom(ofGetHeight());
        circleRad[i] = 5;
        
              
    }
    
    for (int i = 0 ; i < NUM_POINTS2; i ++)
    {
        circleX2[i] = ofRandom(ofGetWidth());
        circleY2[i] = ofRandom(ofGetHeight());
        circleRad2[i] = 5;
        
        
    }
    

}

//--------------------------------------------------------------
void testApp::update(){
    
    

}

//--------------------------------------------------------------
void testApp::draw(){
 
    
    for( int i = 0; i <NUM_POINTS; i++)
    {
        //ofSetColor(255,255,255);
        ofCircle(circleX[i],circleY[i],circleRad[i]);
        ofCircle(circleX2[i],circleY2[i],circleRad2[i]);
        ofLine(circleX[i],circleY[i],circleX2[i],circleY2[i]);
    
    
        
    }
    for(int i = 0; i <NUM_POINTS2; i ++){
        ofCircle(circleX[i],circleY[i],circleRad[i]);
      ofCircle(circleX2[i],circleY2[i],circleRad2[i]);
      ofLine(circleX[i],circleY[i],circleX2[i],circleY2[i]);
    
    

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
