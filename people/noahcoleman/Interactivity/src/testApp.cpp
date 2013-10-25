#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){


    myRectangles.push_back(ofRectangle(100,100,100,100));
     myRectangles.push_back(ofRectangle(200,100,100,50));
     myRectangles.push_back(ofRectangle(300,100,100,25));
     myRectangles.push_back(ofRectangle(400,100,100,12));
     myRectangles.push_back(ofRectangle(500,100,100,6));
     myRectangles.push_back(ofRectangle(600,100,100,3));

    myColors.push_back(ofColor(ofRandom(255), 255, 0));
        myColors.push_back(ofColor(ofRandom(255), 255, 0));
        myColors.push_back(ofColor(ofRandom(255), 255, 0));
        myColors.push_back(ofColor(ofRandom(255), 255, 0));
        myColors.push_back(ofColor(ofRandom(255), 255, 0));
        myColors.push_back(ofColor(ofRandom(255), 255, 0));



}




//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

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
