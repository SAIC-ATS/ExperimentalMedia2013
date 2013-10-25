#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    serialCount = 0;
    firstContact = false;
    
    xPos = ofGetWindowWidth()/2;
    yPos = ofGetWindowHeight()/2;
    
    mySerial.setup("/dev/tty.usbmodemfd141", 9600); //Need a serial port, please. fd141 for home iMac. 3a21 for iMac in 416.
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(bgColor);
    ofSetColor(fgColor);
    ofFill();
    ofCircle(xPos, yPos, 20);
}

//--------------------------------------------------------------
void testApp::serialEvent(ofSerial mySerial){
    int inByte = mySerial.readByte();
    if (firstContact == false){
        if (inByte == 'A') {
            mySerial.flush();
            firstContact = true;
            mySerial.writeByte('A');
        }
    }
    else {
        serialInArray[serialCount] = inByte;
        serialCount++;
        if (serialCount > 2) {
            xPos = serialInArray[0];
            yPos = serialInArray[1];
            fgColor = serialInArray[2];
            
            cout << serialInArray << endl;
            
            mySerial.writeByte('A');
            serialCount = 0;
            
        }
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
