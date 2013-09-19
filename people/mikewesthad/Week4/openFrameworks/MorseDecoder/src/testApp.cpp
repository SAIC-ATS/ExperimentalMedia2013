#include "testApp.h"

#define CAM_WIDTH 320
#define CAM_HEIGHT 240

ofVideoGrabber vidGrabber;
int camWidth = CAM_WIDTH;
int camHeight = CAM_HEIGHT;
int camDisplayX = 0;
int camDisplayY = 100;

ofTexture grayscaleLastFrame;
ofTexture grayscaleFrame;
ofPixels grayscaleLastFramePixels;
ofPixels grayscaleFramePixels;
float deltaIntensities[CAM_WIDTH][CAM_HEIGHT];
ofTexture deltaIntensitiesTexture;
ofPixels deltaIntensitiesPixels;
float changeThreshold = 225.0;
float changeRadius = 5.0;

const int STATE_WAITING_FOR_USER = 0;
const int STATE_DETECTING_FLASHING_LED = 1;
const int STATE_REAL_TIME_ANALYSIS = 2;
int state = 0;

float maxChange;
int xMaxChange;
int yMaxChange;

//--------------------------------------------------------------
void testApp::setup(){
    // Create a ofVideoGrabber object to get frames from the webcam
    //  The width and height are re-set after creating the vidGrabber
    //  because you aren't guaranteed to get the size you asked for
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(camWidth, camHeight);
    camWidth = vidGrabber.width;
    camHeight = vidGrabber.height;

    // Get the memory for the various data structures we will use
    // in getting the changes in pixel intensity
    grayscaleFrame.allocate(camWidth, camHeight, GL_RGB);
    grayscaleLastFrame.allocate(camWidth, camHeight, GL_RGB);
    float deltaIntensities[camWidth][camHeight];
    deltaIntensitiesTexture.allocate(camWidth, camHeight, GL_RGB);
    deltaIntensitiesPixels.allocate(camWidth, camHeight, OF_PIXELS_RGB);
}

//--------------------------------------------------------------
void testApp::update(){

    // Load the next frame from the webcam (if there is one)
    vidGrabber.update();

    if (state == STATE_WAITING_FOR_USER) {

        if(vidGrabber.isFrameNew()) {
            // Load the pixels from the last frame
            grayscaleLastFrame.readToPixels(grayscaleLastFramePixels);

            // Load the new frame and its associated pixels
            grayscaleFrame.loadData(vidGrabber.getPixelsRef());
            grayscaleFrame.readToPixels(grayscaleFramePixels);

            // Loop through each pixel location in the image:
            //      Determine how much the intensity of said pixel has changed since the last frame
            //      Threshold this change so that we can get rid of background noise
            //      Store this change in intensity into a 2D array representing the intensity change for each pixel
            //      Keep track of the maximum intensity change - this is what we are going to assume is the LED location
            // NOTE: the maxChange variable tracks the maximum intensity change, but it only updates
            // if an intensity change exceeds threshold.  This means that if we have sucessfully
            // 'thresholded' away the noise, the location of maxChange should not change when the LED blinks off
            maxChange = 0.0;
            for (int x=0; x<camWidth; x++) {
                for (int y=0; y<camHeight; y++) {
                    ofColor c1 = grayscaleFramePixels.getColor(x, y);
                    ofColor c2 = grayscaleLastFramePixels.getColor(x, y);
                    float intensity1 = (c1.r + c1.b + c1.g)/3.0;
                    float intensity2 = (c2.r + c2.b + c2.g)/3.0;
                    float intensityChange = abs(intensity1 - intensity2);

                    if (intensityChange < changeThreshold) intensityChange = 0.0;
                    else {
                        if (intensityChange > maxChange) {
                            maxChange = intensityChange;
                            xMaxChange = x;
                            yMaxChange = y;
                        }
                    }

                    deltaIntensities[x][y] = intensityChange;

                    // Store the intensity change in an ofPixel object so that we can visualize it
                    deltaIntensitiesPixels.setColor(x, y, ofColor(intensityChange, intensityChange, intensityChange));
                }
            }
            // Load the ofPixel object into a texture so we can render it
            deltaIntensitiesTexture.loadData(deltaIntensitiesPixels);

            // Load the current frame into our object holding the last frame, so we are ready on the next loop
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

    // Draw the webcam image (ofSetColor controls the tint that gets applied to the image)
    ofSetColor(255,255,255);
    vidGrabber.draw(camDisplayX, camDisplayY, camWidth, camHeight);


    if (state == STATE_WAITING_FOR_USER) {
        // Draw the change in intensity from the last frame to the current
        ofSetColor(255,255,255);
        deltaIntensitiesTexture.draw(camDisplayX+camWidth, camDisplayY);

        // Draw information about how to set up the LED detection
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("Hold/place LED up/near the webcam", 15, 10);
        ofDrawBitmapString("Press enter when threhold and radius are properly set to overlap LED", 15, 30);
        ofDrawBitmapString("Change Threshold (Increase/Decrease with w/s keys): "+ofToString(changeThreshold), 15, 50);
        ofDrawBitmapString("Change Radius (Increase/Decrease with a/d keys): "+ofToString(changeRadius), 15, 70);

        // Visualize where the system currently 'thinks' the LED is (i.e. location of max intensity change)
        ofNoFill();
        ofSetLineWidth(3);
        ofSetColor(0, 255, 0);
        ofCircle(camDisplayX+xMaxChange, camDisplayY+yMaxChange, changeRadius);
    }
    else if (state == STATE_DETECTING_FLASHING_LED) {
    }
    else if (state == STATE_REAL_TIME_ANALYSIS) {
    }


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (state==STATE_WAITING_FOR_USER) {
        if (key==OF_KEY_RETURN) state = STATE_DETECTING_FLASHING_LED;

        if (key == 'w' && changeThreshold<255)      changeThreshold += 5.0;
        else if (key == 's' && changeThreshold>0)   changeThreshold -= 5.0;
        if (key == 'd' && changeRadius)             changeRadius += 1.0;
        else if (key == 'a' && changeRadius>1)      changeRadius -= 1.0;
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
