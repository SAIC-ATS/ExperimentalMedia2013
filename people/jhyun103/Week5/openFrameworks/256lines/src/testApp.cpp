#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
      

    
}


//--------------------------------------------------------------
void testApp::draw(){
    
  /*  for (x = 0; x < 256; x++) {
     
        
        if (x%2 == 0) {
            ofSetColor(255, 0, 0);
            ofFill();
            ofLine(x, y, x, ofGetScreenHeight());  
            cout << "x is even " <<endl;
            
        }
        else
        {
            ofSetColor(255,255,0);
            ofFill();
            ofLine(x, y, x, ofGetScreenHeight());

            
        }
    }*/
    
    
    //256 lines gradient 
    
  for (x = 0; x < 256; x++) {
        
        ofSetColor(256-x);
        ofFill();
        ofLine(x, y, x, ofGetScreenHeight());
        


    }
    


