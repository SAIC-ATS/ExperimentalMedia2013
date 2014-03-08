#pragma once

#include "ofMain.h"
#include "GUI.h"

class testApp : public ofBaseApp{

	public:

    // CUSTOM DESTROYER TO CLEAN UP POINTER
    
        virtual ~testApp();
    
    
    // OF DEFAULT METHODS
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y );
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
    
    // CUSTOM METHODS
    
        void processRootMusicDir();
        void searchLibrary(string searchTerms, bool artist, bool album, bool track);

    // VARS
    
        string pathToRoot;
    
    // XML
    
        ofXml XML;
    
    // POINTER TO THE GUI
    
        GUI* theGUI;
};
