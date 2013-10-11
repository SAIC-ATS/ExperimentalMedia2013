#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	camWidth 		= 640;	// try to grab at this size.
	camHeight 		= 480;
    num =16;
	
    //we can now get back a list of devices. 
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName; 
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl; 
        }
	}
    pixelsR.resize(num);
    pixelsG.resize(num);
    pixelsB.resize(num);
    for(int i=0;i<num-1;i++){
        pixelsR[i] = 1;
          pixelsG[i] = 1;
         pixelsB[i] = 1;
    }
    
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoInverted 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);	
	ofSetVerticalSync(true);
}


//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(100,100,100);
	
	vidGrabber.update();
	
	if (vidGrabber.isFrameNew()){
		totalPixels = camWidth*camHeight*3;
		pixels = vidGrabber.getPixels();
        
        //-su
        totalR =0;
        totalG =0;
        totalB =0;
        for (int i = 1; i < totalPixels -1; i+=3){
            
            red = pixels[i-1];
            green = pixels[i];
            blue = pixels[i+1];
            
            totalR += red;
            avR = totalR/(camWidth*camHeight);
            
            totalG += green;
            avG = totalG/ (camWidth*camHeight);
            
            totalB += blue;
            avB = totalB/(camWidth*camHeight);
            
        
//		for (int i = 0; i < totalPixels; i++){
//			videoInverted[i] = 255 - pixels[i];
//		}
//		videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
	}
        
    }

    for (int i =0; i < num-1; i ++){
        pixelsR[i] = pixelsR[i+1];
        pixelsG[i] = pixelsG[i+1];
        pixelsB[i] = pixelsB[i+1];
    }
        pixelsR[num-1] = int(avR);
        pixelsG[num-1] =int(avG);
        pixelsB[num-1] = int(avB);
    

}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0xffffff);
	vidGrabber.draw(0,0);
     ofFill();
    for(int i =0; i < num; i ++){
    ofSetColor(pixelsR[i],pixelsG[i], pixelsB[i]);
    ofRect(i*40+camWidth, 0, 40, camHeight);
	//videoTexture.draw(20+camWidth,20,camWidth,camHeight);
    }
    cout<< pixelsR[num-1] << endl;
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	// Video settings no longer works in 10.7
	// You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343        
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
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
