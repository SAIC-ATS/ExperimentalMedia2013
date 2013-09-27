#include "Week5mirong.h"

//--------------------------------------------------------------
void Week5mirong::setup(){
    
    mode = '0'; // red and yellow lines


}

//--------------------------------------------------------------
void Week5mirong::update(){

}

//--------------------------------------------------------------
void Week5mirong::draw(){
	   
    ofBackground(0, 0, 0);
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("0 --> red and yellow lines, 1 --> grey gradient", 50, 50);
    
    for (int i=0;i<256;i++) {
        
        switch(mode) {
            case '0':
            {   if (i % 2 == 0 ) {
                    ofSetColor(255, 0, 0);
                } else {
                    ofSetColor(255, 255, 0);
                }
                break;
            }
            case '1':
            {
                ofSetColor (i, i, i);
                break;
            }
                
        }
    
        
        ofLine(i * 2 + 100, 100, i * 2 + 100, 500);
        
    }
    
    
}

//--------------------------------------------------------------
void Week5mirong::keyPressed(int key){
    
    if (key == '1' or key == '0') 
        mode = key;        

}

//--------------------------------------------------------------
void Week5mirong::keyReleased(int key){

}

//--------------------------------------------------------------
void Week5mirong::mouseMoved(int x, int y){
    
    ofSetColor(255, 0, 0);
    ofDrawBitmapString("mouse moved!!!!", x, y);

}

//--------------------------------------------------------------
void Week5mirong::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Week5mirong::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Week5mirong::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Week5mirong::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Week5mirong::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Week5mirong::dragEvent(ofDragInfo dragInfo){ 

}