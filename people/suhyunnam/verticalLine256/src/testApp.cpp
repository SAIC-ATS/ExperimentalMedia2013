#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(255, 255, 255);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
   
    //#4-0
    /* 
    ofSetColor(255, 0, 0);
    for(int i =10; i < ofGetWidth(); i = i+10){
    ofLine(i,0,i,ofGetHeight());
    }
     */
  
    
    //#4-1
    /* 
    for(int i =0; i < ofGetWidth(); i ++){
        if ( i%2 == 0){
        ofSetColor(255, 255, 0);
        }else{
            ofSetColor(255, 0, 0);
        }
        ofLine(i,0,i,ofGetHeight());
    }
     */
    
    //#4-2
   
    for(int i =0; i < ofGetWidth(); i ++){
    int iC = (int)ofMap(i, 0, ofGetWidth(), 255, 0);
        ofSetColor(iC, iC, iC);
        ofLine(i,0,i,ofGetHeight());
    }
   
    
        
}
