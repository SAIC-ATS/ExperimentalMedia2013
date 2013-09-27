#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    serial.setup("/dev/tty.usbmodem621", 9600); // address of arduino, baudrate has to be same as in Arduino
    
    potValue1 = 0;
    potValue2 = 0;
    
    
    ofSetBackgroundAuto(false);
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
            
            
            vector<string> bufferVector = ofSplitString(buffer, ",");
            
            potValue1 = ofToInt(bufferVector[0]);
            potValue2 = ofToInt(bufferVector[1]);
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

    
    ofFill();
    ofSetColor(0, 255, 0);
    ofCircle(mouseX, mouseY, 5);

    cout << potValue1 << endl;
    cout << potValue2 << endl;
    
    
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
