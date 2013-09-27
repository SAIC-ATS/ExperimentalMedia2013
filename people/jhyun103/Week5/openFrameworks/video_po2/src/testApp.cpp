#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
	ofSetVerticalSync(true);
	frameByframe = false;

	// Uncomment this to show movies with alpha channels
	// fingerMovie.setPixelFormat(OF_PIXELS_RGBA);
    serial.setup("/dev/tty.usbmodemfd131",9600);
    
    
    
    // initialize the potValue = 0
    potValue = 0;
    potValue2= 0;

	fingerMovie.loadMovie("movies/fingers.mov");
	fingerMovie.play();
}

//--------------------------------------------------------------
void testApp::update(){
    fingerMovie.update();
    
    
    while (serial.available()>0)
    {
        
        
        char myByte = serial.readByte();
        
        if (myByte == '\r' ){
            //nothing nothing nothing 
        }
        
        
        else if (myByte == '\n')
                  {
                      
                      bytes = ofSplitString(buffer, ",");
                      potValue = ofToInt(bytes[0]);
                      potValue2 = ofToInt(bytes[1]);
                      
                      cout << "potValue is " << potValue << endl;
                      cout << "potValue2 is " << potValue2 << endl;
                      
                      
                      buffer.clear();
    }
        
        else
        {
            buffer += myByte ;
            //buffer = buffer + myByte ;
        }
}
}
//--------------------------------------------------------------
void testApp::draw(){

	//ofSetHexColor(0xFFFFFF);
    
    fingerMovie.draw(20,20);
   // ofSetHexColor(0x000000);
    
    
    //fade in out 
   int backgroundColor = ofMap(potValue2,0,1024,0,255);

   // cout << potValue2 << endl;
ofSetColor (255, 255, 255,backgroundColor);
    
    
    // speed
    if(!frameByframe){
        int width = ofGetWidth();
        float pct = potValue/ (float)width;
        float speed = (2 * pct - 1) * 5.0f;
         fingerMovie.setSpeed(speed);
        
    
	}

 
    
    
 /*   if(frameByframe) ofSetHexColor(0xCCCCCC);
    ofDrawBitmapString("potentiometer speed position",20,340);
    if(!frameByframe) ofSetHexColor(0xCCCCCC); else ofSetHexColor(0x000000);*/
  
   

   if(fingerMovie.getIsMovieDone()){
        ofSetHexColor(0xFF0000);
        ofDrawBitmapString("end of movie",20,440);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
   }

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	/*if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        float speed = (2 * pct - 1) * 5.0f;
        fingerMovie.setSpeed(speed);
	}*/
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(!frameByframe){
        fingerMovie.setPaused(true);
	}
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if(!frameByframe){
        fingerMovie.setPaused(false);
	}
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
