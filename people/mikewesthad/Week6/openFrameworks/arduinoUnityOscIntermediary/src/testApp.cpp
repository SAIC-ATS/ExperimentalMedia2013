#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    // Open a serial connection with arduino on COM5
    serial.setup("COM5", BAUD_RATE);

	// Open an outgoing connection with unity on HOST:SEND_PORT
	sender.setup(HOST, SEND_PORT);

    // Open an incoming connection with unity on RECIEVE_PORT
	receiver.setup(RECIEVE_PORT);

	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void testApp::update(){

    // Read the states from Unity via OSC and Arduino via serial
    readArduinoState();
    readUnityState();

    // If the state of the arduino has changed, then send a message to
    // Unity for a specified duration
    if (arduinoMessageChanged) {
        if (currentArduinoChangeMessageSignal < numberChangeMessageSignals) {
            sendArdunioStateToUnity();
        }
        else arduinoMessageChanged = false;
        currentArduinoChangeMessageSignal++;
    }

    // If the state of Unity has changed, then send a message to
    // Arduino for a specified duration
    if (unityMessageChanged) {
        if (currentUnityChangeMessageSignal < numberChangeMessageSignals) {
            sendUnityStateToArduino();
        }
        else unityMessageChanged = false;
        currentUnityChangeMessageSignal++;
    }

}

void testApp::sendUnityStateToArduino() {
    // Write a single byte representing the state of unity and then write a newline
    unsigned char outByte = ofToChar(ofToString(unityState));
    bool byteWasWritten = serial.writeByte(outByte);
    bool newlineWasWritten = serial.writeByte('\n');
    if (!byteWasWritten || !newlineWasWritten) cout << "Error writing to serial" << endl;
}

void testApp::readArduinoState() {
    while(serial.available()>0) {
        // Read a single byte
        char charByte = serial.readByte();
        // Ignore newline or carriage return
        if(charByte != '\r' && charByte != '\n') {
            int intByte = ofToInt(&charByte);
            // Valid output from the arduino is a value between 4 and 7
            // and we only care if the arduino has changed states
            if (intByte>=4 && intByte<=7) {
                if (intByte != arduinoState) {
                    arduinoMessageChanged = true;
                    currentArduinoChangeMessageSignal = 0;
                    arduinoState = intByte;
                }
            }
            else cout << "Unexpected message from arduino: " << charByte << endl;
        }
    }
}

void testApp::readUnityState() {
	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage(&m);

        // If the message address matches unity, there is a single int argument in the message
		if(m.getAddress() == "/unity/state") {
            int newUnityState = m.getArgAsInt32(0);
            if (newUnityState != unityState) {
                unityMessageChanged = true;
                currentUnityChangeMessageSignal = 0;
                unityState = newUnityState;
            }
		}
		// Otherwise, we have an unrecogonized message
		else cout << "Unexpected OSC message at address: " << m.getAddress()<< endl;

	}
}

void testApp::sendArdunioStateToUnity() {
	ofxOscMessage m;
	m.setAddress("/arduino/state");
	m.addIntArg(arduinoState);
	sender.sendMessage(m);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	ofxOscMessage m;
	m.setAddress("/unity/state");
	m.addIntArg((int)ofRandom(0,3));
	sender.sendMessage(m);
}

//--------------------------------------------------------------
void testApp::draw(){

	ofBackground(bgColor);

    // Interpret and draw the arduino state
	ofDrawBitmapString("Arduino State", 10, 30);
    ofFill();
	if (arduinoState == 4) {
        ofSetColor(ledOnColor);
        ofCircle(30,70,10);
        ofCircle(60,70,10);
	}
	else if (arduinoState == 5) {
        ofSetColor(ledOnColor);
        ofCircle(30,70,10);
        ofSetColor(ledDisconnectedColor);
        ofCircle(60,70,10);
	}
	else if (arduinoState == 6) {
        ofSetColor(ledDisconnectedColor);
        ofCircle(30,70,10);
        ofSetColor(ledOnColor);
        ofCircle(60,70,10);
	}
	else if (arduinoState == 7) {
        ofSetColor(ledDisconnectedColor);
        ofCircle(30,70,10);
        ofSetColor(ledDisconnectedColor);
        ofCircle(60,70,10);
	}
	ofSetColor(outlineColor);
	ofNoFill();
    ofCircle(30,70,11);
    ofCircle(60,70,11);

    // Interpret and draw the unity state
	ofDrawBitmapString("Unity State", 10, 130);
    ofFill();
	if (unityState == 0) {
        ofSetColor(ledOnColor);
        ofCircle(30,170,10);
        ofCircle(60,170,10);
	}
	else if (unityState == 1) {
        ofSetColor(ledOnColor);
        ofCircle(30,170,10);
        ofSetColor(ledDisconnectedColor);
        ofCircle(60,170,10);
	}
	else if (unityState == 2) {
        ofSetColor(ledDisconnectedColor);
        ofCircle(30,170,10);
        ofSetColor(ledOnColor);
        ofCircle(60,170,10);
	}
	else if (unityState == 3) {
        ofSetColor(ledDisconnectedColor);
        ofCircle(30,170,10);
        ofSetColor(ledDisconnectedColor);
        ofCircle(60,170,10);
	}
	ofSetColor(outlineColor);
	ofNoFill();
    ofCircle(30,170,11);
    ofCircle(60,170,11);

    // Set the color for all the text
    ofSetColor(outlineColor);

    // Display the framerate
    ofDrawBitmapString(ofToString(ofGetFrameRate())+" fps", 10, 245);

    // Draw the OSC host and port information
	string buf = "sending osc messages to " + string(HOST) + " on port " + ofToString(SEND_PORT);
	ofDrawBitmapString(buf, 10, 300);
	buf = "listening for osc messages on port " + ofToString(RECIEVE_PORT);
	ofDrawBitmapString(buf, 10, 320);
    ofDrawBitmapString(msg_string, 10, 340);

    // Draw strings if information is being transferred through oF to Unity or Arduino
    if (arduinoMessageChanged) ofDrawBitmapString("Message to Unity: "+ofToString(arduinoState), 10, 380);
    if (unityMessageChanged) ofDrawBitmapString("Message to Arduino: "+ofToString(unityState), 10, 400);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
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

