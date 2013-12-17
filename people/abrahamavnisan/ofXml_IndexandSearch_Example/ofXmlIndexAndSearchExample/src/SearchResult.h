#pragma once

#include "ofMain.h"
#include "XMLToText.h"
#include "ToggleHandle.h"

// this class stores all the information we need for a single
// search result, and draws that search result to the screen

class SearchResult: public ofRectangle
{
public:
    
    // A TYPEDEF TO MAKE THINGS A LITTLE EASIER

        typedef std::shared_ptr<SearchResult> SharedPtr;
    
    // CTOR AND DTOR (AKA CONSTRUCTOR AND DESTRUCTOR)

        SearchResult(
                     const int resultCount,
                     const string artistName,
                     const string albumName,
                     const string trackTitle,
                     const string resultPath,
                     const unsigned int uniqueID,
                     const ofRectangle& rectangle);
    
        ~SearchResult();

    // BASIC METHODS
    
        void setup();
        void draw();
    
    // ADVANCED METHODs

        string getOutputText(
//                             const int resultCount,
//                             const string artistName,
//                             const string albumName,
//                             const string trackTitle,
//                             const ofRectangle rectangle
                             );

        void hoverResults(const ofVec2f mouse);

    
    // AND SOME VARS
        
        ofTrueTypeFont resultFont;
        ofTrueTypeFont hoverFont;
        ofColor bgColorEven;
        ofColor bgColorOdd;
    
        string artistName;
        string albumName;
        string trackTitle;
        string resultPath;

        string outputText;
        string headerText;
        
        float textXPos;
        float textYPos;
        float margin;
    
        int resultCount;


};