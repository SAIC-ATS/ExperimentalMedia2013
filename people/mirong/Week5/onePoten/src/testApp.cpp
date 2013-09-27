#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    serial.setup("/dev/tty.usbmodem1421", 9600);

}

//--------------------------------------------------------------
void testApp::update()
{
    unsigned char byteBuffer[1024];
    
    while(serial.available())
    {
        int numByteWritten =serial.readBytes(byteBuffer, 1024);
        buffer.set((char*)byteBuffer, numByteWritten);
        //cout << buffer.getFirstLine() << endl;
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetBackgroundColor(0, 0, 0);
    float r;
    char* string = buffer.getBinaryBuffer();
    r = strtof(string, NULL) / 1023 * 200;
    ofCircle(300, 400, r); // left eye
    ofCircle(700, 400, r); // right eye
    

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
