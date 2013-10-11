#include "miKim6.h"

//--------------------------------------------------------------
void miKim6::setup(){
    
    serial.setup("/dev/tty.usbmodem1411", 9600);
    ofColor red(255, 0, 0);
    ofColor green(0, 255, 0);
    ofColor yellow(255, 255, 0);
    
    colors[0] = green;
    colors[1] = yellow;
    colors[2] = red;
    
    vLedStateBuffer[0] = '0';
    vLedStateBuffer[1] = '0';
    vLedStateBuffer[2] = '0';

    ofBackground(0, 0, 0);
    //ofFill();
    
    h = ofGetWindowHeight();
    w = ofGetWindowWidth();
    
    vButton[0].setFromCenter(w*1/4, h*3/4, 200, 200);
    vButton[1].setFromCenter(w*2/4, h*3/4, 200, 200);
    vButton[2].setFromCenter(w*3/4, h*3/4, 200, 200);
    
    isClicked[0] = false;
    isClicked[1] = false;
    isClicked[2] = false;
    
}

//--------------------------------------------------------------
void miKim6::update(){
    
    // send the status of three virtual buttons to Arduino 
    unsigned char vButtonStateBuffer[3];
    
    for (int i=0; i < 3; i++) {
        if (isClicked[i]) {
            vButtonStateBuffer[i] = '1';
        } else {
            vButtonStateBuffer[i] = '0';
        }
    }

    int nByteWritten = serial.writeBytes(vButtonStateBuffer, 3);
    int nByteRead = serial.readBytes(vLedStateBuffer, 3);

}

//--------------------------------------------------------------
void miKim6::draw(){
    
    drawButton();
    
    for (int i=0; i<3 ; i++) {
        if (vLedStateBuffer[i] == '1') {
            ofSetColor(colors[i]);
        } else {
            ofSetColor(128, 128, 128);
        }
        ofCircle(w*(i+1)/4, h/4, 100, 100);

    }
  

}

// if a button is clicked, its color toggles between red and grey.  
void miKim6::drawButton() {
    
    for (int i=0; i<3; i++) {
        
        ofSetColor(128, 128, 128);
        if (isClicked[i]) {
            ofSetColor(colors[i]);
        }
        ofRect(vButton[i].getPosition(), vButton[i].getWidth(), vButton[i].getHeight());
                    // draw buttons on Window based on infos contained in ofRectangle classes.

    }
    
}

//--------------------------------------------------------------
void miKim6::keyPressed(int key){

}

//--------------------------------------------------------------
void miKim6::keyReleased(int key){

}

//--------------------------------------------------------------
void miKim6::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void miKim6::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void miKim6::mousePressed(int x, int y, int button){
    
    for (int i=0; i < 3; i++) {
                
        if (vButton[i].inside(x, y)) {
            isClicked[i] = !isClicked[i];
        }
    }

}

//--------------------------------------------------------------
void miKim6::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void miKim6::windowResized(int w, int h){

}

//--------------------------------------------------------------
void miKim6::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void miKim6::dragEvent(ofDragInfo dragInfo){ 

}