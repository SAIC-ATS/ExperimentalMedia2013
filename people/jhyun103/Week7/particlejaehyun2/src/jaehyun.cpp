#include "jaehyun.h"

//------------------------------------------------------------------
jaehyunParticle::jaehyunParticle(){
	attractPoints = NULL;
    testFont.loadFont("Courier New Italic.ttf", 20, true, true, true);
    letter = 'a';
	testChar = testFont.getCharacterAsPoints(letter);
    
    serial.setup("/dev/tty.usbmodemfa141", 9600);
      potvalue = 0;
   
}


//------------------------------------------------------------------
void jaehyunParticle::setAttractPoints( vector <ofPoint> * attract ){
	attractPoints = attract;
}

//------------------------------------------------------------------
void jaehyunParticle::reset(){
	//the unique val allows us to set properties slightly differently for each particle
	uniqueVal = ofRandom(-10000, 10000);
	
	pos.x = ofRandomWidth();
	pos.y = ofRandomHeight();
	
	vel.x = ofRandom(-1,1);
	vel.y = ofRandom(-1,1);
	
	frc   = ofPoint(0,0,0);
	
//	scale = ofRandom(0.5, 20);
	

    drag  = ofRandom(0.97, 0.99);
    vel.y = fabs(vel.y) * 3.0; //make the particles all be going down
	
}

//------------------------------------------------------------------
void jaehyunParticle::update(){
   
    
    while(serial.available() > 0)
    {
        // Read a single byte
        char myByte = serial.readByte(); // a "char" is just like a byte
        //cout << "myByte is " << myByte << endl;
        
        // If our byte is an \r that means that we don't want to add it to
        // our buffer to later turn it into a number, but we instead want to
        // just want to ignore it.
        
        if(myByte == '\r') {
            //cout << "myByte == '\r'!" << endl;
            // nothing -- we are waiting for the \n
        }
        // if it is not \r then we check to see if it is an \n
        else if(myByte == '\n')
        {
            // if it IS an \n then we know the buffer is full and can be
            // converted into our int potValue for processing.
            
            potvalue = ofToInt(buffer);
            
            
            // we then clear our buffer so that we can start adding the next
            // incoming bytes that will form our next number.
            buffer.clear();
        }
        else{    
            buffer += myByte;
        }
    }
    
        
    

    
    unsigned char x = (unsigned char)ofMap(potvalue,0,1024,0,1024,true);
    
    unsigned char y= (unsigned char)ofMap(potvalue,0,1024,0,768,true);
	//1 - APPLY THE FORCES BASED ON WHICH MODE WE ARE IN 
	ofPoint attractPt(ofGetMouseX(),ofGetMouseY());
		//ofPoint attractPt(x,y);
		frc = attractPt-pos; // we get the attraction force/vector by looking at the mouse pos relative to our pos
		frc.normalize(); //by normalizing we disregard how close the particle is to the attraction point 
		
		vel *= drag; //apply drag
		vel += frc * 0.6; //apply force
	
		

	
	
	//2 - UPDATE OUR POSITION
	
	pos += vel; 
	
	
	//3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN 
		if( pos.x > ofGetWidth() )
        {
		pos.x = ofGetWidth();
		vel.x *= -1.0;
	}
        else if( pos.x < 0 ){
		pos.x = 0;
		vel.x *= -1.0;
	}
	if( pos.y > ofGetHeight() ){
		pos.y = ofGetHeight();
		vel.y *= -1.0;
	}
	else if( pos.y < 0 ){
		pos.y = 0;
		vel.y *= -1.0;
	}
    
    
   

		
}

//------------------------------------------------------------------
void jaehyunParticle::draw(){


    //ofSetColor(ofMap(age,0,50,255,0));
	
	//ofCircle(pos.x, pos.y, scale * 4.0);
    
    
	string str = "";
	str += char(letter);
    
	testFont.drawString(str, pos.x,pos.y);

}


void jaehyunParticle::keyPressed(int key){
    
    if(key==OF_KEY_ESC) return;
    
testChar = testFont.getCharacterAsPoints(key);
letter = key;
    
}
