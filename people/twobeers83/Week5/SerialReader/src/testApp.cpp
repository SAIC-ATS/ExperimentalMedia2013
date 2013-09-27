#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    serial.setup("/dev/tty.usbmodem621", 9600); // address of arduino, baudrate has to be same as in Arduino
    
    potValue = 0;
    
    ofSetCircleResolution(100);
    ofBackground(255,255,255);
    ofSetVerticalSync(true);
    fillColor.set(255, 0, 0); // red
}

//--------------------------------------------------------------
void testApp::update(){
    
    while(serial.available() > 0)
    {
        char myByte = serial.readByte();
        
        if(myByte == '\r') {
            // do nothing
        }
        else if(myByte == '\n') {
            potValue = ofToInt(buffer);
            buffer.clear();
        }
        else
        {
            buffer += myByte;
        }
        
    }
    
    

}

//--------------------------------------------------------------
void testApp::draw(){


    int potHue = ofMap(potValue, 0, 1024, 0, 255);
    fillColor.setHue(potHue);
    
    ofBackground(255, 255, 255);
    ofSetColor(100, 0, 50);
    ofFill();
    ofSetColor(fillColor);
    ofSetLineWidth(7);
    ofCircle(400, 400, 200);
    
    int potRotate = ofMap(potValue, 0, 1024, 0, 360);
   
    
    ofPushMatrix();
        ofTranslate(400, 400);
        ofRotate(potRotate);

        ofSetColor(0, 0, 0);
        ofSetLineWidth(10);
        ofLine(0, 0, 0, -100);
    
        ofPushMatrix();
            ofRotate(potRotate*12);
            ofSetLineWidth(5);
            ofLine(0, 0, 0, -180);
    ofPopMatrix();
    ofPopMatrix();
    
    
    cout << potValue << endl;
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
