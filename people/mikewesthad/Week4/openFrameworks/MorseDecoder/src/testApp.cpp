/*
Michael Hadley
09/19/13
morseDecoder
(The code could still use some cleaning up, reorganzing and commenting...)

This international morse code decoder makes a few assumptions:
    That the biggest intensity pixel change on your webcam will be the LED
    That the LED is stationary
    That the dot timing is some multiple of 0.25 seconds
    That we are using international morse code (dot=1, dash=3, space=1, letter_break=3, word_break=7)
Parameter Settings:
    The meaning of the parameters is described below.  The settings that seemed to work for me
    were to set the change threshold high, the change radius high and the blink threshold to a value that
    best matches my visual perception of ON/OFF.  Setting the blink threshold too high or too low
    would mean that dots were detected as longer than spaces or vice versa.


The flow of the code is that it moves through five states:

STATE_DETECTING_LED_LOCATION
    Here, the difference in intensities between frames from the webcam is used to isolate
    what is changing in the scene.  A threshold is applied to separate change from not-change. The
    user can adjust this threshold until only the LED is detected as change.  The area of maximum
    change is assumed to be the center of the LED.  Then the user can adjust the radius of a circle
    positioned at that 'center' of the LED.  The program will only process change that occurs within
    that circle.

STATE_DETECTING_BLINK_THRESHOLD
    Now that the location of the LED is known, we want to know when it is on and when it is off.  The
    intensity of the LED is calculated by taking an average of the light intensity within that circle
    (okay, it's really a square) that was determined in the last state.  We can then apply another threshold
    to this 'LED intensity' to separate ON and OFF light levels of intensity.

STATE_DETECTING_MIN_DOT_TIMING
    Once we know when the LED is ON/OFF, we can determine what the dot timing is for the morse code.  NOTE: We
    make the assumption that the timing is some multiple of 0.25 seconds.  We can then watch the LED as it
    blinks and determine how long each blink is.  When the LED blinks ON, it could either mean a dot or a dash,
    so in order to distinguish between the two, we can just track the minimum blink time (since dots < dashes).

STATE_WAITING_FOR_NEW_LETTER
    Almost ready to decode!  But first, we need to make sure that we won't start processing the morse code
    mid-character.  So this state just causes the program to wait until it sees a break between letters or a
    break between words.

STATE_REAL_TIME_ANALYSIS
    Yes! Decoding!  In this state, we watch the LED and track the time that it is ON/OFF.  We can then use that
    timing information to determine what the morse code is (using international morse conventions):
        A dots (ON for a length = 1 dot)
        A dash (ON for a length = 3 dots)
        A space between dots/dashes (OFF for a length = 1 dot)
        A space between letters (OFF for a length = 3 dots)
        A space between words (OFF for a length = 7 dot)
    NOTE: when processing the timing information, we essentially round it to the nearest symbol, i.e.,
    if the signal was an ON flash, then we assume it was a dot if the time was closest to dot time or a
    dash if it was closest to dash time.

STATE_FINISHED
    All done :)

*/

#include "testApp.h"

// Use the smallest camera possible in the hopes that it will have the fastest
// framerate (and that it will take the least time to process)
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
const int STATE_FINISHED = 5;
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

        // If nothing has changed, keep track of time
        if (wasLEDOn && isLEDOn) {
            LEDTimer += ofGetLastFrameTime();
        }
        // Something has changed
        else {
            // The LED turned OFF
            if (wasLEDOn) {
                // Round before setting new value
                minDotTime = min(minDotTime, roundDotTime(LEDTimer));
            }
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

        // If nothing has changed, keep track of time
        if (wasLEDOn == isLEDOn) {
            LEDTimer += ofGetLastFrameTime();
        }
        // Something has changed
        else {
            // The LED turned ON
            if (!wasLEDOn) {
                // Estimate what we think the past ON signal was in morse code:
                //  A space between dots and dashes (length = 1 dot)
                //  A letter break between characters (length = 3 dots)
                //  A word break (length = 7 dots)
                float spaceDifference = abs(LEDTimer-minDotTime);
                float letterDifference = abs(LEDTimer-3.0f*minDotTime);
                float wordDifference = abs(LEDTimer-7.0f*minDotTime);

                // If the best fit is a letter break or a word break, then we can
                // safely start processing the LED without worrying about starting
                // in the middle of a morse code character
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

        // If nothing has changed for longer than two word breaks,
        // let's just assume we have hit the end of the message.
        if (LEDTimer > 14.0*minDotTime) {
            decodedMessage += morseToEnglish(currentMorseCharacter);
            currentMorseCharacter = "";
            cout << "OFF classified as final letter break" << LEDTimer << endl;
            state = STATE_FINISHED;
        }

        // Check if the LED has changed
        if (wasLEDOn == isLEDOn) {
            LEDTimer += ofGetLastFrameTime();
        }
        else {
            // LED just turned off
            if (wasLEDOn) {
                // Estimate what we think the past ON signal was in morse code:
                //  A dots (length = 1 dot)
                //  A dash (length = 3 dots)
                // Add the corresponding dot or dash to our running morse character

                // Dot
                if (abs(LEDTimer-minDotTime) <= abs(LEDTimer-3.0f*minDotTime)) {
                    currentMorseCharacter += ".";
                    cout << "ON classified as . " << LEDTimer << endl;
                }
                // Dash
                else {
                    currentMorseCharacter += "-";
                    cout << "ON classified as - " << LEDTimer << endl;
                }
            }
            // LED just turned on
            else {
                // Estimate what we think the past ON signal was in morse code:
                //  A space between dots and dashes (length = 1 dot)
                //  A letter break between characters (length = 3 dots)
                //  A word break (length = 7 dots)
                float spaceDifference = abs(LEDTimer-minDotTime);
                float letterDifference = abs(LEDTimer-3.0f*minDotTime);
                float wordDifference = abs(LEDTimer-7.0f*minDotTime);

                // Space between dots and dashes
                if (spaceDifference <= letterDifference && spaceDifference <= wordDifference){
                    currentMorseCharacter += " ";
                    cout << "OFF classified as space" << LEDTimer << endl;
                }
                // Letter break
                //  Our currentMorseCharacter is complete, so process it and add it to the decoded message
                else if (letterDifference <= spaceDifference && letterDifference <= wordDifference){
                    decodedMessage += morseToEnglish(currentMorseCharacter);
                    currentMorseCharacter = "";
                    cout << "OFF classified as letter break" << LEDTimer << endl;
                }
                // Word break
                //  Our currentMorseCharacter is complete, so process it and add it to the decoded message
                else {
                    decodedMessage += morseToEnglish(currentMorseCharacter);
                    decodedMessage += " ";
                    currentMorseCharacter = "";
                    cout << "OFF classified as word break" << LEDTimer << endl;
                }
            }
            LEDTimer = 0.0;
        }
    }
    else if (state == STATE_FINISHED) {
    }


}

// Standard international dot time is 0.25 seconds, so lets assume
// that the dots, dash and spaces we are recieving are some multiple of
// 0.25.  If that is true, then we can round our dot times to the nearest 0.25.
float testApp::roundDotTime(float t) {
    float floorTime = floor(t);
    float decimalTime = t - floorTime;
    float roundedDecimalTime = 0.0;
    if (decimalTime <= 0.25/2.0) roundedDecimalTime = 0.0;
    else if (decimalTime <= 0.25 + 0.25/2.0) roundedDecimalTime = 0.25;
    else if (decimalTime <= 0.5 + 0.25/2.0) roundedDecimalTime = 0.5;
    else if (decimalTime <= 0.75 + 0.25/2.0) roundedDecimalTime = 0.75;
    else roundedDecimalTime = 1.0;
    return floorTime + roundedDecimalTime;
}

// Apply a threshold to determining whether a particular light intensity is
// considered on or off
bool testApp::checkIfLEDIsOn(float intensity) {
    if (intensity > blinkThreshold) return true;
    else                            return false;
}

// If we have an estimated location and an estimate radius
// we can get perform a spatial average over all pixel locations
// within that radius to get an average estimated intensity for the LED
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
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("The red dot will appear on the screen to the left of the webcam image when I 'see' a flash from the LED", 15, 10);
        ofDrawBitmapString("Press enter when blink threhold is properly set to overlap LED", 15, 30);
        ofDrawBitmapString("Change Blink Threshold (Increase/Decrease with w/s keys): "+ofToString(blinkThreshold), 15, 50);

        drawEstimatedLED();
    }
    else if (state == STATE_DETECTING_MIN_DOT_TIMING) {
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("I am now trying to estimate the minimum dot timing. Wish me luck.", 15, 10);
        ofDrawBitmapString("Press enter when the timing is properly set.", 15, 30);
        ofDrawBitmapString("The minimum dot time is: "+ofToString(minDotTime)+" seconds", 15, 50);

        drawEstimatedLED();
    }
    else if (state == STATE_WAITING_FOR_NEW_LETTER) {
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("OKAY okay, almost there.  Just waiting for the start of a new letter.", 15, 10);

        drawEstimatedLED();
    }
    else if (state == STATE_REAL_TIME_ANALYSIS) {
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("Current Morse Character: "+currentMorseCharacter, 15, 10);
        ofDrawBitmapString("Current Decoded Message: "+decodedMessage, 15, 30);

        drawEstimatedLED();
    }
    else if (state == STATE_FINISHED) {
        // Draw information about how to set up the blink detection
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("End of message. How'd I do: "+decodedMessage, 15, 10);
        ofDrawBitmapString("Current Morse Character: "+currentMorseCharacter, 15, 30);

        drawEstimatedLED();
    }
}

// Visualize when the estimated LED by placing a red circle on a rectangle the size of the webcam
void testApp::drawEstimatedLED() {
    ofFill();
    ofSetColor(255, 255, 255);
    ofRect(camDisplayX+camWidth, camDisplayY, camWidth, camHeight);
    if (isLEDOn) {
        ofSetColor(255, 0, 0);
        ofCircle(camDisplayX+camWidth+xMaxChange, camDisplayY+yMaxChange, changeRadius);
    }
}

// Handle the adjustment of variables and switching between states
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

