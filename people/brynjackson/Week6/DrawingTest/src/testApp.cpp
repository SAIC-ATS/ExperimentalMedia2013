#include "testApp.h"


int x[50];
int y[50];
int x2[50];
int y2[50];

int lineWidth = 1;
int positions[50][2];

//--------------------------------------------------------------
void testApp::setup(){
    
    serial.setup("/dev/tty.usbmodem1411",9600);
    
    potValue=0;
    
    for(int i=0; i<50; i++){

    x[i]= ofRandom(0,1024);
    y[i]= ofRandom(0,768);
    x2[i] = ofRandom(0,1024);
    y2[i] = ofRandom(0,768);

    }
    
   
        

  
}

//--------------------------------------------------------------
void testApp::update(){
    
    int j = 0;
    
    while(serial.available()>0){
        j++;
        char myByte=serial.readByte();
        
        if(myByte=='\r'){
            
    }
        else if(myByte=='\n'){
            potValue=ofToInt(buffer);
            
            buffer.clear();
        }
        else{
            buffer+=myByte;
            
        }
    }
    cout<<potValue<<endl;

    for(int i=0; i<50; i++){
        
    x[i]+=(.1*(x2[i]-x[i]));
    y[i]+=(.1*(y2[i]-y[i]));
    
    if(ofDist(x[i], y[i], x2[i], y2[i]) < 20){
      
        x2[i] = ofRandom(0,1024);
        y2[i] = ofRandom(0,768);
    }


    }

}


//--------------------------------------------------------------
void testApp::draw(){
        float f=ofMap(potValue,0,1023,1,120);
    ofSetFrameRate(f);
    
ofBackground(255,255,255);
    
for(int i=0; i<50; i++){
        for(int i2=0; i2<50; i2++){
            if(i2 != i)
    
    ofSetColor(0,0,0);
    
    ofCircle(x[i], y[i], 5);
        
    ofLine(x[i],y[i],x[i2],y[i2]);
            
        }
    }
    

    
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
