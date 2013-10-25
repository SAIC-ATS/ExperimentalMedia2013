#include "testApp.h"
//You have to do math to figure out what the ranges should be. First, figure out
//the distance the laser will be from the surface.  Now, figure out what the angle
//of travel will need to be to go from edge to edge on the surface.  Subtract half
//of that angle from 90 to get the min, and add half the angle to 90 to get the max.
//Repeat for the y axis.
unsigned char servoXRangeMin = 75; //the min number to send to servoX
unsigned char servoXRangeMax = 105; //the max number to send to servoX
unsigned char servoYRangeMin = 80; //the min number to send to servoY
unsigned char servoYRangeMax = 100; //the max number to send to servoY
unsigned char packetEnd = 254; //the byte sent to signal the end of a packet
unsigned char laserOn = 255;   //the byte sent to turn laser on
unsigned char laserOff = 0;    //the byte sent to turn laser off



//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(30);
    serial.setup("/dev/tty.usbmodem1421",9600);
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(false);
        ofBackground(0);
    

}

//--------------------------------------------------------------
void testApp::update(){
   

}

//--------------------------------------------------------------
void testApp::draw(){
    //BACKGROUND
    ofSetColor(0,0,0,10);//black with 10% alpha
    ofRect(0,0,ofGetWidth(),ofGetHeight());//cover screen with rectangle
    
    //VIRTUAL LASER POINTER
    ofSetColor(200 ,153, 255,90);//purpley with 80% alpha
    ofCircle(mouseX, mouseY, 5);
    
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
    //GLOWING GREEN TRAIL
    ofSetColor(0,255,0,90);//nice GITD green!
    ofCircle(mouseX, mouseY, 10);
    
    // this will take the value of the mouse X position, scale it to 0-180
    // and cast it into an unsigned char (a byte) so it can be sent.
    // We also set clamping to TRUE which will further ensure that the range is
    // always within 0-180.
    unsigned char scaledMouseX = (unsigned char)ofMap(ofGetMouseX(),0,ofGetWindowWidth(),servoXRangeMax,servoXRangeMin,true);
    
    // likewise with mouse y
    unsigned char scaledMouseY = (unsigned char)ofMap(ofGetMouseY(),0,ofGetWindowHeight(),servoYRangeMax,servoYRangeMin,true);
    
    // send the x byte
    serial.writeByte(scaledMouseX);
    
    // send the y byte
    serial.writeByte(scaledMouseY);
    
    //tell the laser to turn on (Because Arduino is going to read this as
    //an analog value, I changed the laser on/off to 255 and the packet boundary to 254
    
    serial.writeByte(255);//Keep laser on
    
    // since we do not allow the range to go outside 0-254, we can send the 255
    // byte as a packet boundary marker to signal the end of our packet.
    serial.writeByte(254);
    
    
    
    
    // REMEMBER that this is sending bytes to the arduino quite quickly
    // 30 times / second (see ofSetFrameRate above).  Thus, on the Arduino
    // end you will only get quick responsiveness if you do your best to avoid
    // using delays in your code!  Otherwise the Arduino Serial ring buffer will fill
    // (because it is s too much data too fast) and you will start losing
    // data points.


}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    // scales and casts mouse x into the range of servo motion
    unsigned char scaledMouseX = (unsigned char)ofMap(ofGetMouseX(),0,ofGetWindowWidth(),servoXRangeMax,servoXRangeMin,true);
    
    // likewise with mouse y
    unsigned char scaledMouseY = (unsigned char)ofMap(ofGetMouseY(),0,ofGetWindowHeight(),servoYRangeMax,servoYRangeMin,true);
    
    // send the x byte
    serial.writeByte(scaledMouseX);
    
    // send the y byte
    serial.writeByte(scaledMouseY);
    
    // turn laser on
    serial.writeByte(laserOn);
    
    // send packet
    serial.writeByte(packetEnd);

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

    // scales and casts mouse x into the range of servo motion
    unsigned char scaledMouseX = (unsigned char)ofMap(ofGetMouseX(),0,ofGetWindowWidth(),servoXRangeMax,servoXRangeMin,true);
    
    // likewise with mouse y
    unsigned char scaledMouseY = (unsigned char)ofMap(ofGetMouseY(),0,ofGetWindowHeight(),servoYRangeMax,servoYRangeMin,true);
    
    // send the x byte
    serial.writeByte(scaledMouseX);
    
    // send the y byte
    serial.writeByte(scaledMouseY);
    
    // turn laser off
    serial.writeByte(laserOff);
    
    // send packet
    serial.writeByte(packetEnd);


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
