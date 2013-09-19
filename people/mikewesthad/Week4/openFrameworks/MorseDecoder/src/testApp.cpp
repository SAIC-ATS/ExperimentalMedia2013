#include "testApp.h"

#define CAM_WIDTH 320
#define CAM_HEIGHT 240

ofVideoGrabber vidGrabber;
int camWidth = CAM_WIDTH;
int camHeight = CAM_HEIGHT;

ofTexture grayscaleLastFrame;
ofTexture grayscaleFrame;
ofPixels grayscaleLastFramePixels;
ofPixels grayscaleFramePixels;
float deltaIntensities[CAM_WIDTH][CAM_HEIGHT];
ofTexture deltaIntensitiesTexture;
ofPixels deltaIntensitiesPixels;
float threshold = 225.0;

const int STATE_WAITING_FOR_USER = 0;
const int STATE_DETECTING_FLASHING_LED = 1;
const int STATE_REAL_TIME_ANALYSIS = 2;
int state = 0;

float maxChange;
int xMaxChange;
int yMaxChange;

//--------------------------------------------------------------
void testApp::setup(){
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(camWidth, camHeight);
    camWidth = vidGrabber.width;
    camHeight = vidGrabber.height;

    grayscaleFrame.allocate(camWidth, camHeight, GL_RGB);
    grayscaleLastFrame.allocate(camWidth, camHeight, GL_RGB);
    float deltaIntensities[camWidth][camHeight];
    deltaIntensitiesTexture.allocate(camWidth, camHeight, GL_RGB);
    deltaIntensitiesPixels.allocate(camWidth, camHeight, OF_PIXELS_RGB);
}

//--------------------------------------------------------------
void testApp::update(){

    vidGrabber.update();

    if (state == STATE_WAITING_FOR_USER) {
        if(vidGrabber.isFrameNew()) {
            grayscaleLastFrame.readToPixels(grayscaleLastFramePixels);
            grayscaleFrame.loadData(vidGrabber.getPixelsRef());
            grayscaleFrame.readToPixels(grayscaleFramePixels);

            maxChange = 0.0;
            for (int x=0; x<camWidth; x++) {
                for (int y=0; y<camHeight; y++) {
                    ofColor c1 = grayscaleFramePixels.getColor(x, y);
                    ofColor c2 = grayscaleLastFramePixels.getColor(x, y);
                    float intensity1 = (c1.r + c1.b + c1.g)/3.0;
                    float intensity2 = (c2.r + c2.b + c2.g)/3.0;
                    float intensityChange = abs(intensity1 - intensity2);
                    if (intensityChange < threshold) {
                        intensityChange = 0.0;
                    }
                    else {
                        if (intensityChange > maxChange) {
                            maxChange = intensityChange;
                            xMaxChange = x;
                            yMaxChange = y;
                        }
                    }
                    deltaIntensities[x][y] = intensityChange;
                }
            }

            for (int x=0; x<camWidth; x++) {
                for (int y=0; y<camHeight; y++) {
                    float delta = deltaIntensities[x][y];
                    deltaIntensitiesPixels.setColor(x, y, ofColor(delta, delta, delta));
                }
            }
            deltaIntensitiesTexture.loadData(deltaIntensitiesPixels);

            grayscaleLastFrame.loadData(vidGrabber.getPixelsRef());
        }
    }
    else if (state == STATE_DETECTING_FLASHING_LED) {
    }
    else if (state == STATE_REAL_TIME_ANALYSIS) {
    }


}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0, 0, 0);
    ofSetColor(255,255,255);
    vidGrabber.draw(0, 0, camWidth, camHeight);


    if (state == STATE_WAITING_FOR_USER) {
        ofSetColor(255, 255, 255);
        deltaIntensitiesTexture.draw(camWidth, camHeight);
        ofDrawBitmapString("Hold/place LED up/near the webcam and press enter", 15, 10);
        ofDrawBitmapString(ofToString(threshold), 15, 30);
        ofCircle(xMaxChange, yMaxChange, 5);
    }
    else if (state == STATE_DETECTING_FLASHING_LED) {
    }
    else if (state == STATE_REAL_TIME_ANALYSIS) {
    }


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if ((state==STATE_WAITING_FOR_USER) && (key==OF_KEY_RETURN)) {
        state = STATE_DETECTING_FLASHING_LED;
    }

    if (key == 'w') threshold += 5.0;
    if (key == 's') threshold -= 5.0;

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
