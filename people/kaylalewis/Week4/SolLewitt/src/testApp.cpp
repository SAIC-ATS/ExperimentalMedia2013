#include "testApp.h"

float xLocation [50];
float yLocation [50];
int rColor = 0;
int gColor = 50;
int bColor = 150;

int width;
int height;
bool imAwake = false;

//--------------------------------------------------------------
void testApp::setup(){
    width = ofGetWidth();
    height = ofGetHeight();
    
    for(int fuckit = 0;fuckit < totalpoints; fuckit++) //+=1 or -- is -=1
    {
        xLocation[fuckit] = ofRandom (0,width);
        yLocation [fuckit] = ofRandom (0,height);
    }
}

//--------------------------------------------------------------
void testApp::update()
{


}

//--------------------------------------------------------------
void testApp::draw()
{
    if(imAwake)
    {
        ofBeginSaveScreenAsPDF("LewisLewitt");
        ofBackground(0);
        ofSetColor(rColor, gColor, bColor);
        for(int sf = 0; sf < totalpoints; sf++)
        {
            for(int scrap = 0; scrap < totalpoints; scrap ++)
            {
                if(scrap != sf)
                {
                    ofLine(xLocation[sf], yLocation [sf], xLocation [scrap], yLocation [scrap]);
                }
            }
            
            ofCircle(xLocation[sf], yLocation [sf], 8);
            
            
        }
        ofEndSaveScreenAsPDF();
        imAwake = false;
    }
    ofBackground(0);
    ofSetColor(rColor, gColor, bColor);
    for(int sf = 0; sf < totalpoints; sf++)
    {
        for(int scrap = 0; scrap < totalpoints; scrap ++)
        {
            if(scrap != sf)
            {
                ofLine(xLocation[sf], yLocation [sf], xLocation [scrap], yLocation [scrap]);
            }
        }
                
        ofCircle(xLocation[sf], yLocation [sf], 8);
        
        
    }
    

}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    if (key == 32)
    {
        for(int fuckit = 0;fuckit < totalpoints; fuckit++) //+=1 or -- is -=1
        {
        xLocation[fuckit] = ofRandom (0,width);
        yLocation [fuckit] = ofRandom (0,height);
        }
    
    }
    
        
    if (key == 's')
    {
        
        {imAwake = true;}
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------

