#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    serial.setup("/dev/tty.usbmodem621", 9600);   
    // address of arduino, baudrate has to be same as in Arduino
    
    potValue1 = 0;
    potValue2 = 0;
    
    ofBackground(255);
    strokeColor.set(255,0,0);
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
            
            
            cout << "My un-split buffer is = " << buffer << endl;
            cout << "The size of my split bufferVector = " << bufferVector.size() << " and I was expecting 2" << endl;
            
            if(bufferVector.size() < 2) {
                cout << "The size of my buffer is less than 2!!!!" << endl;
                cout << "If I do anything my program will crash!  So I'll just skip it." << endl;
                
            } else {
                potValue1 = ofToInt(bufferVector[0]);
                potValue2 = ofToInt(bufferVector[1]);
            }
            
                        
            
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

    int xAxis = ofMap(potValue1, 0, 680, 0, 1024);
    int yAxis = ofMap(potValue2, 0, 1024, 0, 768);
    
    
    strokeColor.setHue(strokeColor.getHue()+1);
    if(strokeColor.getHue() > 254) strokeColor.setHue(0);
    
    ofFill();
    ofSetColor(strokeColor);
    ofCircle(xAxis, yAxis, 5);
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key ==' ') {
        ofBackground(255);
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
