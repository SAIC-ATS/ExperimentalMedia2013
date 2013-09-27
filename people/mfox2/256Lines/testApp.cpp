#include "testApp.h"

float height = 0;
//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0);

	height = ofGetHeight();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	for(int i = 0; i < 256; i++)
	{
		if(i%2 == 0)
		{
			ofSetColor(255, 255, 0);
		}
		if(i%2 != 0)
		{
			ofSetColor(255, 0, 0);
		}

		ofLine(i, height/4 , i, 3*height/4);
	}

	for(int i = 0; i < 256; i++)
	{
		ofSetColor(255-i);
		ofLine(i+256, height/4, i+256, 3*height/4);
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