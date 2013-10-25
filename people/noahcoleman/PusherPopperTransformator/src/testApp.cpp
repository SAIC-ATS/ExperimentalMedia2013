#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    angleDegrees = 0;
    radius = 100;

}

//--------------------------------------------------------------
void testApp::update(){
    angleDegrees += 2;
    scaleX += ofRandom(-2,2);
    scaleY += ofRandom(-2,2);
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    float centerX = ofGetWidth() / 2;
    float centerY = ofGetHeight() / 2;
    
    ofPushMatrix();
    ofTranslate(centerX, centerY);// creates new origin at (centerX,centerY)
    
    
    ofSetColor(180, 90, 0);
    ofFill();
    ofEllipse(0, 0, 20, 20);
    ofRotateZ(angleDegrees/10);
    //ofLine(0, 0, radius, 0);
    
    //this push matrix will inherit the existing transformations
    ofPushMatrix();
    ofTranslate(radius, 0);

    ofSetColor(0, 90, 255);
    ofFill();
    ofEllipse(0, 0, 10, 10);
    ofRotateZ(angleDegrees);
    //ofLine(0, 0, radius, 0);
    
    ofSetColor(200);
    ofFill();
    ofPushMatrix();
    ofTranslate(radius/2, 0);
    // ofScale(scaleX, scaleY);
    ofEllipse(0, 0, 10, 10);

    
    
    ofPopMatrix();
    
    ofPopMatrix();
    
    ofPopMatrix();
    
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
