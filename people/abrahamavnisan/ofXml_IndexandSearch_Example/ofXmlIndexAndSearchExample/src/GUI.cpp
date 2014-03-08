//  Created by Abraham Avnisan on 12/8/13.

#include "GUI.h"
#include "testApp.h"

// defining some constants comes in handy when we
// are laying all this stuff out
#define SIZE_H1 27
#define SIZE_H2 14
#define SIZE_H3 12
#define MARGIN 20

//--------------------------------------------------------------
GUI::GUI(const string pathToRoot){
    GUI::setup(pathToRoot);
}
//--------------------------------------------------------------
GUI::~GUI(){
    
    // because we have occasion to use pointers (regular, old "dumb"
    // pointers, rather than "smart" pointers like std::shared_ptr,
    // we need to take care to delete them ourselves.  We do this
    // by extending the destroyer method (ie, what we are doing here.)
    delete rootDirDisplay;
    delete selectButton;
    delete searchBar;
    delete searchButton;
    delete nextButton;
    delete previousButton;
    delete headerText;
}
//--------------------------------------------------------------
void GUI::setup(const string pathToRoot){
    
// LOAD FONTS
    
    h1.loadFont("Calibri.ttf", SIZE_H1, true, false, true);
    h2.loadFont("Calibri.ttf", SIZE_H2, true, false, true);
    h3.loadFont("Calibri.ttf", SIZE_H3, true, false, true);
    
    // setup the text box to display the root directory
    ofRectangle myRect(MARGIN, 35, 550, 20);
    rootDirDisplay = new TextInput(myRect, pathToRoot, false);
    
    // setup the "select root dir" button
    ofRectangle myRect2(550 + MARGIN + 20, 46, 20, 20);
    selectButton = new Button(myRect2, "select", 11);
    
    // setup the filter toggles    
    vector<int> toggleRectXCoordinates;
    toggleRectXCoordinates.push_back(20);
    toggleRectXCoordinates.push_back(85);
    toggleRectXCoordinates.push_back(160);
    
    for (int i = 0; i < 3; i++)
    {
        int xPos = toggleRectXCoordinates[i];
        ofRectangle toggleRect(xPos,102,14,14);
        std::shared_ptr<ToggleHandle> myToggle = std::shared_ptr<ToggleHandle>(new ToggleHandle(toggleRect));
        searchFilters.push_back(myToggle);
    }
    
    // setup the search bar
    ofRectangle myRect4(MARGIN, 125, 550, 20);
    searchBar = new TextInput(myRect4, "enter search terms", true);

    // setup the "search" button
    ofRectangle myRect3(550 + MARGIN + 18.5, 136, 20, 20);
    searchButton = new Button(myRect3, "search", 11);
    
    // setup the previousButton for our pager
    ofRectangle previousRect(50, 660, 20, 20);
    previousButton = new Button(previousRect, "PREV", 11);
    previousButton->drawOutline = false;
    
    // setup the nextButton for our pager
    ofRectangle nextRect(575, 660, 20, 20);
    nextButton = new Button(nextRect, "NEXT", 11);
    nextButton->drawOutline = false;
    
    // initialize our display pane header text
    ofRectangle headerRect(21, 194, 653, 20);
    headerText = new SearchResult(0, "ARTIST", "ALBUM", "TRACK", "none", 0, headerRect);
    
    // initialize boolean event vars
    processRootDir = false;
    updateResults = false;
    searchLibrary = false;
    
    // initialize search filter vars
    searchArtists = false;
    searchAlbums = false;
    searchTracks = false;
    
    // initialize pager vars
    nextPageExists = false;
    previousPageExists = false;
    currentPage = 1;
    numPages = 1;
    
    // initialize our typeStr variable
    typeStr = "";
}
//--------------------------------------------------------------
void GUI::update(){
    
    // by calculating the previous and next pages in the update
    // method we only ever have to worry about keeping track of
    // the current page
    
    previousPage = currentPage - 1;
    nextPage = currentPage + 1;
    
    // this is also the place from which we will keep track of
    // other of our pager vars
    
    if (currentPage > 1) previousPageExists = true;
    else previousPageExists = false;
    
    if (currentPage < numPages) nextPageExists = true;
    else nextPageExists = false;
    
    // update the vars associated with the HOVER method
    // in the SearchResult class
    currentTime = ofGetSystemTime();
    elapsedTime = currentTime - lastTime;
    if (elapsedTime > 300) hover = true;
    else hover = false;
}
//--------------------------------------------------------------
void GUI::draw(){
    
// In this method we lay out the GUI, one element at a time
    
    // basic setup
    ofBackground(255);
    ofSetColor(0);
    ofEnableAlphaBlending();
    ofEnableAntiAliasing();
    
//    // draw our heading
//    string heading = "Select your iTunes music library to index\nand search it!";
//    h1.drawString(heading, MARGIN, MARGIN+SIZE_H1);
    
    // draw the next line
    string heading2 = "iTunes library root directory:";
    h2.drawString(heading2, MARGIN, 25);

    // and the next one
    string searchHeading = "Search your library for music:";
    h2.drawString(searchHeading, MARGIN, 90);
    
    // write our search filter labels
    string artist = "artist";
    string album = "album";
    string track = "track";
    h3.drawString(artist, 40, 113);
    h3.drawString(album, 105, 113);
    h3.drawString(track, 183, 113);
    
    // call the draw methods for our class instances
    rootDirDisplay->draw();
    selectButton->draw();
    searchButton->draw();
    searchBar->draw();
    for (int i = 0; i < searchFilters.size(); i++)
    {
        searchFilters[i]->draw();
    }

    // draw our header (only when results are showing)
    if (!(results.empty())) headerText->draw();

    // draw our results pane (we aren't drawing the results
    // themselves here, just the display pane itself)
    resultsPane();
    
    // if search result vector isn't empty...
    if (!(results.empty()))
    {
        // draw our search results
        for (int i = 0; i < results.size(); i++)
        {
            results[i]->draw();
        }
        // if we are displaying results, we will also want
        // to give the user some information about what page
        // she is looking at
        string pagerStats;
        pagerStats = "displaying " + ofToString(currentPage) + "/" + ofToString(numPages) + " pages";
        float statsWidth = h3.stringWidth(pagerStats);
        float xPos = (ofGetWidth() / 2) - (statsWidth/2);
        h3.drawString(pagerStats, xPos, 662);
    }
    // if our search result vector IS empty, we should let
    // the user know that there are no results to display
    else
    {
        string noResults = "There are currently no results to display";
        float noResultsWidth = h2.stringWidth(noResults);
        float xPos = 350 - (noResultsWidth/2);
        h2.drawString(noResults, xPos, 385);
    }
    
    // draw our pager buttons if appropriate
    if (nextPageExists) nextButton->draw();
    if (previousPageExists) previousButton->draw();
    
    // if user hovers mouse over a result, we will call the hoverResults
    // method
    if ( (hover) && (!(results.empty())) )
    {
        ofVec2f mouse;
        mouse.x = ofGetMouseX();
        mouse.y = ofGetMouseY();
        
        for (int i = 0; i < results.size(); i++)
        {
            results[i]->hoverResults(mouse);
        }
    }
    
    
    
}
//--------------------------------------------------------------
void GUI::resultsPane(){
    
    ofColor activeColor(0);

    ofPushStyle();
    
    ofSetColor(0);
    
    ofRectangle resultsTab(20, 170, 180, 25);
    ofVec2f topLeft1 = resultsTab.getTopLeft();
    ofVec2f topRight1 = resultsTab.getTopRight();
    ofVec2f bottomRight1 = resultsTab.getBottomRight();
    ofVec2f bottomLeft1 = resultsTab.getBottomLeft();
    
    ofRectangle blankTab(200, 170, 475, 25);
    ofVec2f topLeft2 = blankTab.getTopLeft();
    ofVec2f topRight2 = blankTab.getTopRight();
    ofVec2f bottomRight2 = blankTab.getBottomRight();
    ofVec2f bottomLeft2 = blankTab.getBottomLeft();

    ofRectangle display(20, 195, 655, 440);
    ofVec2f topLeft3 = display.getTopLeft();
    ofVec2f topRight3 = display.getTopRight();
    ofVec2f bottomRight3 = display.getBottomRight();
    ofVec2f bottomLeft3 = display.getBottomLeft();
   
    // draw the top, right and left of the search results rect
    ofLine(topLeft1, topRight1);
    ofLine(topLeft1, bottomLeft1);
    ofLine(topRight1, bottomRight1);

    // draw the bottom, right and left of the display rect
    ofLine(bottomLeft3, bottomRight3);
    ofLine(topLeft3, bottomLeft3);
    ofLine(topRight3, bottomRight3);

    ofSetColor(activeColor);
    h2.drawString("Search Results", 50, 175+SIZE_H2);

    // draw bottom of imported tab
    ofLine(bottomLeft2, bottomRight2);

    ofPopStyle();
}
//--------------------------------------------------------------
void GUI::pagedResults(){
    
    // this method creates instances of our SearchResult class in order
    // to draw the search results to the screen 

    // reset the event boolean and pager vars
    updateResults = false;
    
    // clear our results vector
    results.clear();
    
    // create a local ofXml object for our search results.  The
    // searchResultsXML.xml file is created by the searchLibrary
    // method in testApp.cpp, so all we need to do here is load
    // that file and pull out the information we need from it
    ofXml resultsXML;
    resultsXML.load("searchResultsXML.xml");
    
    // set the xml object to the root node (remember, "//" tells
    // ofXml to search from the root
    resultsXML.setTo("//RESULTS");
    
    // grab the number of results using the getNumChildren method
    int numResults = resultsXML.getNumChildren();
    
    // set the number results to draw which will be determined based
    // on the max number of results we can fit in the results pane
    // at any given time - in our case, 21
    int numResultsToDraw;
    if (numResults < 21) numResultsToDraw = numResults;
    else numResultsToDraw = 21;
    
    // set the numPages, which is a function of the numResultsToDraw
    if (numResults > 21)
    {
        numPages = ceil(numResults/21.0);
    }
    else
    {
         numPages = 1;
    }
    
    // now we can iterate over the XML file, create instances of our
    // SearchResult class, and push back those instances to our results
    // vector. We start by setting our XML to the first RESULT tag we
    // want to draw, which is a function of our current page.

    int startingResult = (currentPage * numResultsToDraw) - numResultsToDraw;

    // we need to adjust numResultsToDraw if we are on the last page
    // otherwise bad things will happen
    if (currentPage==numPages)
    {
        numResultsToDraw = numResults - startingResult;
    }
    
    //We can do this by taking advantage of ofXml's array-like syntax
    string pathToStartingResult = "//RESULTS/RESULT[" + ofToString(startingResult) + "]";
    resultsXML.setTo(pathToStartingResult);
    
    // once we are at the first element, it's time to iterate over the results, pulling
    // out all the information we need from each one so that we can construct our SearchResult
    // instances
    
    for (int i = 0; i < numResultsToDraw; i++)
    {
        // declare and get values for a set of variables
        // that correspond to our SearchResult construtor
        int resultCount = i+1 + startingResult;
        resultsXML.setTo("artist_name");
        string artistName = resultsXML.getValue();
        resultsXML.setTo("../album_name");
        string albumName = resultsXML.getValue();
        resultsXML.setTo("../track_title");
        string trackTitle = resultsXML.getValue();
        resultsXML.setTo("../path");
        string pathToTrack = resultsXML.getValue();
        resultsXML.setTo("../uniqueID");
        int uniqueID = ofToInt(resultsXML.getValue());
        
        // define the search result rectangle, which will also
        // be passed to our contstructor
        int rectX = 21;
        int rectY = 194 + (20 * (i+1));
        int rectHeight = 20;
        int rectWidth = 653;
        ofRectangle resultRect(rectX, rectY, rectWidth, rectHeight);
        
        // now we actually call our constructor
        SearchResult::SharedPtr thisResult =
        SearchResult::SharedPtr (new SearchResult(resultCount,
                                                  artistName,
                                                  albumName,
                                                  trackTitle,
                                                  pathToTrack,
                                                  uniqueID,
                                                  resultRect));

        // and push_back our searchresult instance to our results vector
        results.push_back(thisResult);
        
        // before repeating this loop, we set the ofXml object
        // back to the "RESULT" element for this result so that
        // we can proceed to the next by calling the setToSibling();
        // method
        resultsXML.setTo("../");
        resultsXML.setToSibling();;
    }
}
//--------------------------------------------------------------
void GUI::keyPressed(const int key){

    // here we record information from the keyboard
    // and send it to our search bar
    if ((key!=2304) && (key!=2305) && (key!=2306) && (key!=13)) // ignore the shift key and the enter key
    {
        if(key == OF_KEY_DEL || key == OF_KEY_BACKSPACE)
        {
            typeStr = typeStr.substr(0, typeStr.length()-1);
        }
        else
        {
            typeStr.append(1, (char)key);
        }
        searchBar->defaultText = typeStr;
    }
}
//--------------------------------------------------------------
void GUI::mouseMoved(const ofVec2f mouse){
    
    // each time the mouse moves, we reset the lastTime var
    // which we use in the update method to determine whether
    // the mouse is hovering
    lastTime = ofGetSystemTime();
    
}
//--------------------------------------------------------------
void GUI::mousePressed(const ofVec2f mouse){
    
    // here we listen for mousePressed events and check to see
    // whether they came from within any of our buttons.  If
    // they did, we set that button isPressed boolean to TRUE
    
    if (selectButton->hitTest(mouse)) selectButton->isPressed = true;
    if (searchButton->hitTest(mouse)) searchButton->isPressed = true;
    if (searchBar->hitTest(mouse)) searchBar->isPressed = true;
    
    for (int i = 0; i < searchFilters.size(); i++)
    {
        if (searchFilters[i]->hitTest(mouse))
        {
            searchFilters[i]->isPressed = true;
        }
    }

}
//--------------------------------------------------------------
void GUI::mouseReleased(const ofVec2f mouse){
    
    // here we listen for mouseReleased events and check to see
    // whether they came from within any of our buttons.  If
    // they did, we set our corresponding booleans
    
    if (selectButton->hitTest(mouse))
    {
        selectButton->isReleased = true;
        selectButton->isPressed = false;
        processRootDir = true;
    }
    
    if (searchButton->hitTest(mouse))
    {
        searchButton->isReleased = true;
        searchButton->isPressed = false;
        searchLibrary = true;
        updateResults = true;
        currentPage = 1;
    }

    if ((nextPageExists) && (nextButton->hitTest(mouse)))
    {
        nextButton->isReleased = true;
        nextButton->isPressed = false;
        updateResults = true;
        currentPage++;
    }
    
    if ((previousPageExists) && (previousButton->hitTest(mouse)))
    {
        previousButton->isReleased = true;
        previousButton->isPressed = false;
        updateResults = true;
        currentPage--;
    }
    
    if (searchBar->hitTest(mouse))
    {
        searchBar->isReleased = true;
        searchBar->isPressed = false;
        
        // clear the default text in our
        // search bar when it is pressed
        typeStr = "";
    }
    
    // check our search filter toggles and set our
    // search filter booleans accordinbly
    if (searchFilters[0]->isSelected)
    {
        searchArtists = true;
    }
    else
    {
        searchArtists = false;
    }
    if (searchFilters[1]->isSelected)
    {
        searchAlbums = true;
    }
    else
    {
        searchAlbums = false;
    }
    if (searchFilters[2]->isSelected)
    {
        searchTracks = true;
    }
    else
    {
        searchTracks = false;
    }
    
    // here we iterate through our search filters to see
    // if the mouse was released inside any of their toggles,
    // setting the isReleased, isPressed and isSelected booleans
    // accordingly (we could do this above, but this seems easier
    // if a bit repetitive)
    for (int i = 0; i < searchFilters.size(); i++)
    {
        if (searchFilters[i]->hitTest(mouse))
        {
            searchFilters[i]->isReleased = true;
            searchFilters[i]->isPressed = false;
            searchFilters[i]->isSelected = !(searchFilters[i]->isSelected);            
        }
    }
}