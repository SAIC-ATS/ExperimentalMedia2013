#include "testApp.h"

int numParticles;

//--------------------------------------------------------------
void testApp::setup(){
    
    
//    numParticles = 50;
//    
//    for(int i = 0; i < numParticles; i++)
//    {
//        Particle particle;
//        
//        particle.position.x = ofGetWidth()/2;//ofRandom(0,ofGetWidth());  // random x position
//        particle.position.y = ofGetHeight()/2;//ofRandom(0,ofGetHeight()); // random y position
//        
//        particle.velocity.x = ofRandom(-5,5);  // random x velocity
//        particle.velocity.y = ofRandom(-5);  // random y velocity
//        
//        particle.acceleration.y = .01;
//        
//        myParticles.push_back(particle); // add it to our vector
//    }
}

//--------------------------------------------------------------
void testApp::update(){
//    for(int i = 0; i < numParticles; i++)
//    {
//        myParticles[i].update();
//    }
    for (int i = 0; i < myParticles.size(); i++) {
        Particle newParticle;
        
    }
    myParticle.update();
    newParticle.update();

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    myParticle.draw();
    newParticle.draw();
    
//    for(int i = 0; i < numParticles; i++)
//    {
//        myParticles[i].draw();
//    }
    
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
