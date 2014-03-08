#pragma once

#include "ofMain.h"
#include "BaseHandle.h"
#include "SearchResult.h"
#include "TextInput.h"
#include "ToggleHandle.h"
#include "Button.h"



class GUI
{
    public:
    
    // CTOR AND DTOR (AKA, CONSTRUCTOR AND DESTRUCTOR)
    
        GUI(const string rootMusicDir);
        virtual ~GUI();
    
    // STANDARD METHODS THAT MIMIC DEFAULT OF METHODS
    
        void setup(const string pathToRoot);
        void update();
        void draw();
        
    // EVENT METHODS "IMPORTED" FROM TESTAPP.CPP

        void keyPressed(const int key);
        void mouseMoved(const ofVec2f mouse);
        void mousePressed(const ofVec2f mouse);
        void mouseReleased(const ofVec2f mouse);
        
    // CUSTOM METHODS TO DISPLAY OUR RESULTS
    
        void resultsPane();
        void pagedResults();
        
    // POINTERS TO OUR CLASS INSTANCES

        TextInput* rootDirDisplay;
        Button* selectButton;
        Button* searchButton;
        TextInput* searchBar;
    
        Button* nextButton;
        Button* previousButton;
    
        SearchResult* headerText;

        // we use shared pointers only when we need them
        std::vector<ToggleHandle::SharedPtr> searchFilters;
        std::vector<SearchResult::SharedPtr> results;
        
    // VARS
        
        string typeStr;
        
        ofTrueTypeFont h1;
        ofTrueTypeFont h2;
        ofTrueTypeFont h3;
    
    // EVENT BOOLEANS
    
        // these booleans are passed between our GUI object and
        // our main testApp.cpp file
        
        bool processRootDir;
        bool searchLibrary;
        bool updateResults;
    
        bool searchArtists;
        bool searchAlbums;
        bool searchTracks;
    
    // PAGER BOOLEANS AND VARS
    
        bool nextPageExists;
        bool previousPageExists;
    
        int currentPage;
        int previousPage;
        int nextPage;
        int numPages;
    
    // VARS TO CHECK FOR MOUSE HOVER
    
        bool hover;
        unsigned long long lastTime;
        unsigned long long currentTime;
        unsigned long long elapsedTime;
    
};

