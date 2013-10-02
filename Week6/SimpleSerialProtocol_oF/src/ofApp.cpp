#include "ofApp.h"

void ofApp::setup()
{
    ofSetFrameRate(30);
    serial.setup("/dev/tty.usbmodem1a1261",9600);
}

void ofApp::update()
{
    // this will take the value of the mouse X position, scale it to 0-254
    // and cast it into an unsigned char (a byte) so it can be sent.
    // We also set clamping to TRUE which will further ensure that the range is
    // always within 0-254.
    unsigned char scaledMouseX = (unsigned char)ofMap(ofGetMouseX(),0,ofGetWidth(),0,254,true);

    // likewise with mouse y
    unsigned char scaledMouseY = (unsigned char)ofMap(ofGetMouseY(),0,ofGetHeight(),0,254,true);

    // send the x byte
    serial.writeByte(scaledMouseX);

    // send the y byte
    serial.writeByte(scaledMouseY);

    // since we do not allow the range to go outside 0-254, we can send the 255
    // byte as a packet boundary marker to signal the end of our packet.
    serial.writeByte(255);

    // REMEMBER that this is sending bytes to the arduino quite quickly
    // 30 times / second (see ofSetFrameRate above).  Thus, on the Arduino
    // end you will only get quick responsiveness if you do your best to avoid
    // using delays in your code!  Otherwise the Arduino Serial ring buffer will fill
    // (because it is getting too much data too fast) and you will start losing
    // data points.
}

void ofApp::draw()
{
    ofBackground(0);

    ofDrawBitmapString("Not much to see here",ofPoint(20,20));
}