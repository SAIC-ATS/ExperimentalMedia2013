#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    int i = 0;
    while (i < points) {
        yValues[i] = ofRandom(ofGetHeight());
        xValues[i] = ofRandom(ofGetWidth());
        i++;
    }
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    // press "p" to snap screenshot
    // press spacebar to draw a new work
    
    if (pdf) {
        ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
    }
    if (reset) {
        int x = 0;
        while (x < points) {
            yValues[x] = ofRandom(ofGetHeight());
            xValues[x] = ofRandom(ofGetWidth());
            x++;
            reset = false;
        }
    }
    ofSetBackgroundColor(255, 255, 255);
    int i = 1;
    while (i < points) {
        ofSetColor(0,0,0);
        ofCircle(xValues[i],yValues[i],1);
        i++;
    }
    i = 1;
    while (i <=points) {
        int i2 = points-1;
        while (i2 >0) {
            //cout << "TOP OF LINE LOOP"  << endl;
            //cout << "LINE DRAWN FROM point number " << i << "to number " << i2 << endl;
            ofLine(xValues[i],yValues[i],xValues[i2],yValues[i2]);
            i2--;
        }
        i++;
    }
    //cout << "end of draw loop" << endl;
    if (pdf) {
        ofEndSaveScreenAsPDF();
        pdf = false;
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key==112) {
        pdf = true;
    }
    if (key==32) {
        reset = true;
    }
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
