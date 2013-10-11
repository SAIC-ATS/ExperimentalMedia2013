#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	
	int num = 15;
	p.assign(num, jaehyunParticle());


	resetParticles();
    
    Img.loadImage("notebook_texture_stock_i_by_lemurianwanderer-d39tnsu.jpg");
}

//--------------------------------------------------------------
void testApp::resetParticles(){

	//these are the attraction points used in the forth demo 
	
	
	attractPointsWithMovement = attractPoints;
	
	for(int i = 0; i < p.size(); i++){
			
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
	}	
}

//--------------------------------------------------------------
void testApp::update(){
	for(int i = 0; i < p.size(); i++){
		
		p[i].update();
	}
	
	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.1) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.1) * 12.0;
	}
    
     
}

//--------------------------------------------------------------
void testApp::draw(){
   ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));
   Img.draw(0,0);
     
    
	for(int i = 0; i < p.size(); i++){
     

		p[i].draw();
    }
    
    

    
	


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

		
	if( key == ' ' ){
		resetParticles();}
   
        
      
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
