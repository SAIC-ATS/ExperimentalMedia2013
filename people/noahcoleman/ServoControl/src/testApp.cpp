#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    mySerial.setup("/dev/tty.usbmodemfd141", 9600); //Need a serial port, please. fd141 for home iMac. 3a21 for iMac in 416.
    

        
    
}

//--------------------------------------------------------------
void testApp::update(){

    
    

}

//--------------------------------------------------------------
void testApp::draw(){
    ofVec2f mouseXy = ofVec2f(ofGetMouseX(), ofGetMouseY()); //creates an ofVec2f (2d vector) called mouseXy and fills it with the mouse x&y data
    ofSetColor(0);
    ofFill();
    ofCircle(mouseXy.x, mouseXy.y, 3);
    
//    vector<ofVec2f> mouseData; //creates a vector called mouseData.  This is a container to store the data so we can send it to the Arduino later.
//    mouseData.push_back(mouseXy); //this fills the container (vector) with the mouseXy data.
    
    //cout << mouseData[0] << endl;
    
    
    mouseXy.x = ofMap(mouseXy.x, 0, ofGetWindowWidth(), 0, 180, true);//maps the mouse location to a scale of 0-180 for the servos
    mouseXy.y = ofMap(mouseXy.y, 0, ofGetWindowWidth(), 0, 180, true);
    mouseXy.x = int(mouseXy.x);//changes the vector data from floats to ints because Arduino don't like floats
    mouseXy.y = int(mouseXy.y);

    ofBuffer outputBuffer;
    
    outputBuffer.append(ofToString(int(mouseXy.x)));
//    outputBuffer.append(",");
//    outputBuffer.append(ofToString(int(mouseXy.y))); //I will use this later when I am sending both x and y values.
    outputBuffer.append("\r\n");
    unsigned char *cArray = (unsigned char*)outputBuffer.getBinaryBuffer();//need to change char array to something writeBytes will like.
    int numBytesWritten = mySerial.writeBytes(cArray, outputBuffer.size());


//    cout << << endl;
//    cout <<mouseXy.x << endl;
//    cout <<mouseXy.y << endl;

    
    
    
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
