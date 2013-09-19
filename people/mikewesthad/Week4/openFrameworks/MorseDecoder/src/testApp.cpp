#include "testApp.h"

#define CAM_WIDTH 160
#define CAM_HEIGHT 120

ofVideoGrabber vidGrabber;
int camWidth = CAM_WIDTH;
int camHeight = CAM_HEIGHT;
int camDisplayX = 0;
int camDisplayY = 100;

ofTexture lastFrame;
ofTexture currentFrame;
ofPixels lastFramePixels;
ofPixels currentFramePixels;
float deltaIntensities[CAM_WIDTH][CAM_HEIGHT];
ofTexture deltaIntensitiesTexture;
ofPixels deltaIntensitiesPixels;
float changeThreshold = 225.0;
float changeRadius = 5.0;

const int STATE_DETECTING_LED_LOCATION = 0;
const int STATE_DETECTING_BLINK_THRESHOLD = 1;
const int STATE_DETECTING_MIN_DOT_TIMING = 2;
const int STATE_WAITING_FOR_NEW_LETTER = 3;
const int STATE_REAL_TIME_ANALYSIS = 4;
int state = 0;

float maxChange;
int xMaxChange;
int yMaxChange;

float blinkThreshold = 100.0;
bool isLEDOn = false;
float LEDTimer = 10.0;          // These need to be defaulted to large values to assure that nothing funky
float minDotTime = 10.0;        // will happen when we first start looking for a dot signal


string decodedMessage = "";
string currentMorseCharacter = "";

//--------------------------------------------------------------
void testApp::setup(){
    // Create a ofVideoGrabber object to get frames from the webcam
    //  The width and height are re-set after creating the vidGrabber
    //  because you aren't guaranteed to get the size you asked for
    vidGrabber.setVerbose(true);
    vidGrabber.listDevices();
    vidGrabber.videoSettings();
    vidGrabber.initGrabber(camWidth, camHeight);
    camWidth = vidGrabber.width;
    camHeight = vidGrabber.height;

    // Get the memory for the various data structures we will use
    // in getting the changes in pixel intensity
    currentFrame.allocate(camWidth, camHeight, GL_RGB);
    lastFrame.allocate(camWidth, camHeight, GL_RGB);
    float deltaIntensities[camWidth][camHeight];
    deltaIntensitiesTexture.allocate(camWidth, camHeight, GL_RGB);
    deltaIntensitiesPixels.allocate(camWidth, camHeight, OF_PIXELS_RGB);
}

//--------------------------------------------------------------
void testApp::update(){

    // Load the next frame from the webcam (if there is one)
    vidGrabber.update();

    if (state == STATE_DETECTING_LED_LOCATION) {

        if(vidGrabber.isFrameNew()) {
            // Load the pixels from the last frame
            lastFrame.readToPixels(lastFramePixels);

            // Load the new frame and its associated pixels
            currentFrame.loadData(vidGrabber.getPixelsRef());
            currentFrame.readToPixels(currentFramePixels);

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
                    ofColor c1 = currentFramePixels.getColor(x, y);
                    ofColor c2 = lastFramePixels.getColor(x, y);
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
            lastFrame.loadData(vidGrabber.getPixelsRef());
        }
    }
    else if (state == STATE_DETECTING_BLINK_THRESHOLD) {
        // Get the current frame
        currentFrame.loadData(vidGrabber.getPixelsRef());
        currentFrame.readToPixels(currentFramePixels);

        // Estimate LED's intensity from the current frame
        float intensity = estimateLEDIntensity();

        // Update whether we think the LED is on or off
        isLEDOn = checkIfLEDIsOn(intensity);

    }
    else if (state == STATE_DETECTING_MIN_DOT_TIMING) {
        // Get the current frame
        currentFrame.loadData(vidGrabber.getPixelsRef());
        currentFrame.readToPixels(currentFramePixels);

        // Estimate LED's intensity from the current frame
        float intensity = estimateLEDIntensity();

        // Update whether we think the LED is on or off
        bool wasLEDOn = isLEDOn;
        isLEDOn = checkIfLEDIsOn(intensity);
        if (wasLEDOn && isLEDOn) {
            LEDTimer += ofGetLastFrameTime();
        }
        else if (wasLEDOn && !isLEDOn) {
            minDotTime = min(minDotTime, LEDTimer);
            LEDTimer = 0.0;
        }
        else {
            LEDTimer = 0.0;
        }
    }
    else if (state == STATE_WAITING_FOR_NEW_LETTER) {
        // Get the current frame
        currentFrame.loadData(vidGrabber.getPixelsRef());
        currentFrame.readToPixels(currentFramePixels);

        // Estimate LED's intensity from the current frame
        float intensity = estimateLEDIntensity();

        // Update whether we think the LED is on or off
        bool wasLEDOn = isLEDOn;
        isLEDOn = checkIfLEDIsOn(intensity);
        if (wasLEDOn == isLEDOn) {
            LEDTimer += ofGetLastFrameTime();
        }
        else {
            if (!wasLEDOn) {
                float spaceDifference = abs(LEDTimer-minDotTime);
                float letterDifference = abs(LEDTimer-3.0f*minDotTime);
                float wordDifference = abs(LEDTimer-7.0f*minDotTime);
                if (letterDifference <= spaceDifference || wordDifference <= spaceDifference) {
                    state = STATE_REAL_TIME_ANALYSIS;
                }
            }

            LEDTimer = 0.0;
        }


    }
    else if (state == STATE_REAL_TIME_ANALYSIS) {
        // Get the current frame
        currentFrame.loadData(vidGrabber.getPixelsRef());
        currentFrame.readToPixels(currentFramePixels);

        // Estimate LED's intensity from the current frame
        float intensity = estimateLEDIntensity();

        // Update whether we think the LED is on or off
        bool wasLEDOn = isLEDOn;
        isLEDOn = checkIfLEDIsOn(intensity);
        if (wasLEDOn == isLEDOn) {
            LEDTimer += ofGetLastFrameTime();
        }
        else {
            if (wasLEDOn) {
                if (abs(LEDTimer-minDotTime) <= abs(LEDTimer-3.0f*minDotTime)) {
                    currentMorseCharacter += ".";
                    cout << "ON classified as . " << LEDTimer << endl;
                }
                else {
                    currentMorseCharacter += "-";
                    cout << "ON classified as - " << LEDTimer << endl;
                }
//                if (approxEqual(LEDTimer, minDotTime, minDotTime)) {
//                    currentMorseCharacter += ".";
//                }
//                else if (approxEqual(LEDTimer, 3*minDotTime, minDotTime)) {
//                    currentMorseCharacter += "-";
//                }
//                else {
//                    cout << "Unknown timing ON... " << LEDTimer << endl;
//                }
            }
            else {
                float spaceDifference = abs(LEDTimer-minDotTime);
                float letterDifference = abs(LEDTimer-3.0f*minDotTime);
                float wordDifference = abs(LEDTimer-7.0f*minDotTime);
                if (spaceDifference <= letterDifference && spaceDifference <= wordDifference){
                    currentMorseCharacter += " ";
                    cout << "OFF classified as space" << LEDTimer << endl;
                }
                else if (letterDifference <= spaceDifference && letterDifference <= wordDifference){
                    decodedMessage += morseToEnglish(currentMorseCharacter);
                    currentMorseCharacter = "";
                    cout << "OFF classified as letter break" << LEDTimer << endl;
                }
                else {
                    decodedMessage += " ";
                    currentMorseCharacter = "";
                    cout << "OFF classified as word break" << LEDTimer << endl;
                }
//                if (approxEqual(LEDTimer, minDotTime, minDotTime)) {
//                    currentMorseCharacter += " ";
//                }
//                else if (approxEqual(LEDTimer, 3*minDotTime, minDotTime)) {
//                    decodedMessage += morseToEnglish(currentMorseCharacter);
//                    currentMorseCharacter = "";
//                }
//                else if (approxEqual(LEDTimer, 7*minDotTime, minDotTime)) {
//                    decodedMessage += " ";
//                    currentMorseCharacter = "";
//                }
//                else {
//                    cout << "Unknown timing OFF... " << LEDTimer << endl;
//                }
            }

            LEDTimer = 0.0;
        }

    }


}

bool testApp::approxEqual(float a, float b, float acceptableRange) {
    if (abs(a-b) < acceptableRange) return true;
    else return false;
}

bool testApp::checkIfLEDIsOn(float intensity) {
    if (intensity > blinkThreshold) return true;
    else                            return false;
}

float testApp::estimateLEDIntensity() {
    float averageIntensity = 0.0;
    float numberPixels = 0.0;
    int minX = xMaxChange - changeRadius;
    int maxX = xMaxChange + changeRadius;
    int minY = yMaxChange - changeRadius;
    int maxY = yMaxChange + changeRadius;
    for (int x=minX; x<maxX; x++) {
        for (int y=minY; y<maxY; y++) {
            ofColor c = currentFramePixels.getColor(x, y);
            float intensity = (c.r + c.b + c.g)/3.0;
            averageIntensity += intensity;
            numberPixels++;
        }
    }
    averageIntensity /= numberPixels;
    return averageIntensity;
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0, 0, 0);

    // Draw the webcam image (ofSetColor controls the tint that gets applied to the image)
    ofSetColor(255,255,255);
    vidGrabber.draw(camDisplayX, camDisplayY, camWidth, camHeight);


    if (state == STATE_DETECTING_LED_LOCATION) {
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

    else if (state == STATE_DETECTING_BLINK_THRESHOLD) {
        // Draw information about how to set up the blink detection
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("The red dot will appear on the screen to the left of the webcam image when I 'see' a flash from the LED", 15, 10);
        ofDrawBitmapString("Press enter when blink threhold is properly set to overlap LED", 15, 30);
        ofDrawBitmapString("Change Blink Threshold (Increase/Decrease with w/s keys): "+ofToString(blinkThreshold), 15, 50);

        // Visualize when the system is detecting a blink by placing it on a rectangle the size of the webcam
        ofFill();
        ofSetColor(255, 255, 255);
        ofRect(camDisplayX+camWidth, camDisplayY, camWidth, camHeight);
        if (isLEDOn) {
            ofSetColor(255, 0, 0);
            ofCircle(camDisplayX+camWidth+xMaxChange, camDisplayY+yMaxChange, changeRadius);
        }
    }
    else if (state == STATE_DETECTING_MIN_DOT_TIMING) {
         // Draw information about how to set up the blink detection
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("I am now trying to estimate the minimum dot timing. Wish me luck.", 15, 10);
        ofDrawBitmapString("Press enter when the timing is properly set.", 15, 30);
        ofDrawBitmapString("The minimum dot time is: "+ofToString(minDotTime)+" seconds", 15, 50);

        // Visualize when the system is detecting a blink by placing it on a rectangle the size of the webcam
        ofFill();
        ofSetColor(255, 255, 255);
        ofRect(camDisplayX+camWidth, camDisplayY, camWidth, camHeight);
        if (isLEDOn) {
            ofSetColor(255, 0, 0);
            ofCircle(camDisplayX+camWidth+xMaxChange, camDisplayY+yMaxChange, changeRadius);
        }
    }
    else if (state == STATE_WAITING_FOR_NEW_LETTER) {
         // Draw information about how to set up the blink detection
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("OKAY okay, almost there.  Just waiting for the start of a new letter.", 15, 10);

        // Visualize when the system is detecting a blink by placing it on a rectangle the size of the webcam
        ofFill();
        ofSetColor(255, 255, 255);
        ofRect(camDisplayX+camWidth, camDisplayY, camWidth, camHeight);
        if (isLEDOn) {
            ofSetColor(255, 0, 0);
            ofCircle(camDisplayX+camWidth+xMaxChange, camDisplayY+yMaxChange, changeRadius);
        }
    }
    else if (state == STATE_REAL_TIME_ANALYSIS) {
        // Draw information about how to set up the blink detection
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("Current Morse Character: "+currentMorseCharacter, 15, 10);
        ofDrawBitmapString("Current Decoded Message: "+decodedMessage, 15, 30);

        // Visualize when the system is detecting a blink by placing it on a rectangle the size of the webcam
        ofFill();
        ofSetColor(255, 255, 255);
        ofRect(camDisplayX+camWidth, camDisplayY, camWidth, camHeight);
        if (isLEDOn) {
            ofSetColor(255, 0, 0);
            ofCircle(camDisplayX+camWidth+xMaxChange, camDisplayY+yMaxChange, changeRadius);
        }
    }


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (state==STATE_DETECTING_LED_LOCATION) {
        if (key==OF_KEY_RETURN) state = STATE_DETECTING_BLINK_THRESHOLD;

        if (key == 'w' && changeThreshold<255)      changeThreshold += 5.0;
        else if (key == 's' && changeThreshold>0)   changeThreshold -= 5.0;
        if (key == 'd' && changeRadius)             changeRadius += 1.0;
        else if (key == 'a' && changeRadius>1)      changeRadius -= 1.0;
    }

    else if (state==STATE_DETECTING_BLINK_THRESHOLD) {
        if (key==OF_KEY_RETURN) state = STATE_DETECTING_MIN_DOT_TIMING;

        if (key == 'w' && blinkThreshold<255)      blinkThreshold += 5.0;
        else if (key == 's' && blinkThreshold>0)   blinkThreshold -= 5.0;
    }

    else if (state==STATE_DETECTING_MIN_DOT_TIMING) {
        if (key==OF_KEY_RETURN) state = STATE_WAITING_FOR_NEW_LETTER;
    }


}

string testApp::morseToEnglish(string m) {
  if (m == ". -")               return "A";
  else if (m == "- . . .")      return "B";
  else if (m == "- . - .")      return "C";
  else if (m == "- . .")        return "D";
  else if (m == ".")            return "E";
  else if (m == ". . - .")      return "F";
  else if (m == "- - .")        return "G";
  else if (m == ". . . .")      return "H";
  else if (m == ". .")          return "I";
  else if (m == ". - - -")      return "J";
  else if (m == "- . -")        return "K";
  else if (m == ". - . .")      return "L";
  else if (m == "- -")          return "M";
  else if (m == "- .")          return "N";
  else if (m == "- - -")        return "O";
  else if (m == ". - - .")      return "P";
  else if (m == "- - . -")      return "Q";
  else if (m == ". - .")        return "R";
  else if (m == ". . .")        return "S";
  else if (m == "-")            return "T";
  else if (m == ". . -")        return "U";
  else if (m == ". . . -")      return "V";
  else if (m == ". - -")        return "W";
  else if (m == "- . . -")      return "X";
  else if (m == "- . - -")      return "Y";
  else if (m == "- - . .")      return "Z";
  else if (m == ". - - - -")    return "1";
  else if (m == ". . - - -")    return "2";
  else if (m == ". . . - -")    return "3";
  else if (m == ". . . . -")    return "4";
  else if (m == ". . . . .")    return "5";
  else if (m == "- . . . .")    return "6";
  else if (m == "- - . . .")    return "7";
  else if (m == "- - - . .")    return "8";
  else if (m == "- - - - .")    return "9";
  else if (m == "- - - - -")    return "0";
  else                          return "";
}

