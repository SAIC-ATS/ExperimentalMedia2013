//
//  Ball.cpp
//  Learning1_0_0
//
//  Created by Noah Coleman on 9/11/13.
//
//

#include "Ball.h"


Ball::Ball(){
    color.set( ofRandom(255), ofRandom(255), ofRandom(255));
    
    x = ofRandom( ofGetWindowWidth());
    y = ofRandom(ofGetWindowHeight());
    
    void Ball::moveTo(){
        
        
    }
    
    void Ball::draw(){
        ofSetColor(color);
        ofFill();
        ofCircle(x, y, 30);
        
    }
}