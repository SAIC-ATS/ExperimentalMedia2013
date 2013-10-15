#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    verdana.loadFont("Verdana.ttf", 100, true, true);
    poem = "push";
    ofToggleFullscreen();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackgroundGradient(ofColor::gray,ofColor(30,10,30), OF_GRADIENT_CIRCULAR);
    ofSetColor(255,255,255);
    if (myAlign) {
        verdana.drawString(poem,(ofGetWidth()*.5)-(verdana.stringWidth("push")/2)-25,ofGetHeight()*.5);
    }
    else
    {
        verdana.drawString(poem,(ofGetWidth()*.5)-(verdana.stringWidth(poem)/2)-25,ofGetHeight()*.5);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key=='f')
    {
        ofToggleFullscreen();
        ofBackground(0,0,0);
    }
    if (key=='a')
    {
        myAlign = !myAlign;
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
//        int i2 = i;
//        if (button==0) {
//            while (i==i2) {
//                i = rand() % 3;     // I couldn't figure out how to do this with a size or sizeof function, though I know there is a way...
//                }
       // string punctuation = punct_array[i];
        poem = "poem";
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    if (button==0) {
        poem = "push";
    }
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
