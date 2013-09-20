#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    onshot = false;
    int width = ofGetWidth();
    int height = ofGetHeight();
    
    for (int i=0;i<50;i++) {
        
        px[i] = ofRandom(0, width);
        py[i] = ofRandom(0, height);
        
    }

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

	if( onshot ){
		ofBeginSaveScreenAsPDF("mikim-"+ofGetTimestampString()+".pdf", false);
	}
    
    ofBackground(0, 0, 0);
    
    for (int i=0;i<50;i++) {
        ofSetColor(200, 0, 0);
        ofCircle(px[i], py[i], 5);
        for (int j=0 ; j<50 ; j++) {
            ofSetColor(128, 128, 128);
            ofLine(px[i], py[i], px[j], py[j]);
        }
    }
    
    if (onshot) {
        ofEndSaveScreenAsPDF();
        onshot = false;
    }
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    onshot = true;

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    
    ofSetColor(255, 0, 0);
    ofDrawBitmapString("mouse moved!!!!", x, y);

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