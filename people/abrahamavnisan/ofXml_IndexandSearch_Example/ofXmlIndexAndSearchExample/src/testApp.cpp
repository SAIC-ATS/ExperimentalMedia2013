//  Created by Abraham Avnisan

#include "testApp.h"


//Poco is a powerful library built in to openFrameworks that
//allows us to use regular expressions, among many other things.
//In fact, ofXml is a wrapper of some poco functionality - though
//working with ofXml in this app doesn't require getting into the
//poco code under the hood.

//For more info on the many amazing uses of poco, check out
//this url: http://pocoproject.org/slides/040-StringsAndFormatting.pdf
//and this one: http://pocoproject.org/documentation/index.html

// to use Poco in our openFrameworks project, we need some
// #includes - which #includes will depend on exactly what you
// want to do with Poco.  These are a good start:

#include "Poco/RegularExpression.h"
#include "Poco/String.h"
using Poco::RegularExpression;

// OF DEFAULT METHODS

//--------------------------------------------------------------
void testApp::setup(){
        
    // inititalize the GUI
    theGUI = new GUI(pathToRoot);
    
    // check to see if an xml file of the indexed music
    // library already exists
    ofFile libraryXML;
    if (libraryXML.open("musicLibrary.xml"))
    {
        // if it does, get the pathToRoot and
        // send it to the GUI
        XML.load("musicLibrary.xml");
        if (XML.setTo("pathToRoot"))
        {
            pathToRoot = XML.getValue();
            theGUI->rootDirDisplay->defaultText = pathToRoot;
        }
    }
    
    // if the file "musicLibrary.xml" doesn't exist,
    // call the processRootMusicDir method
    else processRootMusicDir();
}
//--------------------------------------------------------------


// By passing the update, draw, and basic keyboard and mouse events
// to the GUI we can focus on the XML, ofFile and ofDirectory
// functionality here in the main app
//--------------------------------------------------------------
void testApp::update(){
    
    theGUI->update();
    
    // listen for theGUI's event bool vars and respond accordingly
    if (theGUI->processRootDir) processRootMusicDir();
    if (theGUI->searchLibrary)
    {
        theGUI->searchLibrary = false;
        // we should only call the search method after we verify
        // that there is something to search for
        cout << "typeStr HERE is " << theGUI->typeStr << endl;
        if (theGUI->typeStr != "")
        {
            cout << "searchLibrary called in testApp::update" << endl;
            searchLibrary(theGUI->typeStr, theGUI->searchArtists, theGUI->searchAlbums, theGUI->searchTracks);
        }
    }
    if (theGUI->updateResults)
    {
        theGUI->updateResults = false;
        theGUI->pagedResults();
    }
}
//--------------------------------------------------------------
void testApp::draw(){
    theGUI->draw();
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
    theGUI->keyPressed(key);
}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    ofVec2f mouse(x,y);
    theGUI->mouseMoved(mouse);
}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    ofVec2f mouse(x,y);
    theGUI->mousePressed(mouse);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    ofPushMatrix();
    ofTranslate(0, -115);
    ofVec2f mouse(x,y);
    theGUI->mouseReleased(mouse);
    ofPopMatrix();
}
//--------------------------------------------------------------



// CUSTOM METHODS
//--------------------------------------------------------------
testApp::~testApp(){
    delete theGUI;
    
    // we want to delete our searchResultsXML.xml file when we
    // exit the program, so that we don't show those results
    // accidentally the next time the program is run
    ofFile searchResults;
    if (searchResults.open("searchResultsXML.xml"))
    {
        searchResults.remove();
    }
}
//--------------------------------------------------------------
void testApp::processRootMusicDir(){
    
    // reset theGUI's event boolean
    
    theGUI->processRootDir = false;
    
    // declare local variables

    string pathToSong;
    
    // if we are running this method, we want to make sure we start
    // fresh by clearing and initializing our musicLibrary.xml file
    
    XML.clear();
    XML.addChild("LIBRARY");
    XML.setTo("LIBRARY");
    XML.save("musicLibrary.xml");

    // our regEx_upToRoot finds two directories and a file.  In other words
    // it will find the "Artists --> Albums --> track.mp3" portion of our directory structure.
    RegularExpression regEx_upToRoot("[^/]+/[^/]+/[^/]+$");
        
    // this is how we get a dialog box to pop us that lets us select
    // a file.  Because we are relying on the user's itunes library
    // to be organized in this fashion: Root --> Artists --> Albums --> tracks
    // picking any song in the library will allow us to index the
    // entire library
    ofFileDialogResult openDirResult;
    openDirResult = ofSystemLoadDialog("Select any song in your music library");
    pathToSong = openDirResult.getPath();
    
    // because the RegEx substitution function below changes the string in which it performs
    // the search here we are going to switch out our variables so that the variable name
    // matches what's stored in it.  pathToRoot is also a variable defined in our header file,
    // which means it is globablly available in testApp, something that will come in handy later.
    pathToRoot = pathToSong;

    // Using our upToRoot RegEx, we can then grab the , "Artists --> Albums --> track.mp3"
    // portion of our directory structure, and subsititute it with a blank string ("") using
    // the subst method.
    regEx_upToRoot.subst(pathToRoot, "");
    
    // Add the pathtoroot to the XML file.  Because we only process the music library if it hasn't
    // been processed before, this will allow us to access the path, which we will need to send
    // to the GUI, even when we don't process the whole library
    XML.addValue("pathToRoot", pathToRoot);
    
    // update theGUI with the new pathToRoot
    theGUI->rootDirDisplay->defaultText = pathToRoot;
    
    // open and list the root music library directory
    ofDirectory rootMusicDir;
    rootMusicDir.open(pathToRoot);
    rootMusicDir.listDir();
    
    // create a for loop to iterate through the root directory
    for (int i = 0; i < rootMusicDir.size(); i++)
    {
        // the top level directories are titled by artist name
        // so here we grab the name of each artist before recursively
        // descending into each artist folder and indexing their
        // album names and track titles
        string artist_name = rootMusicDir.getName(i);
        
        // create a local ofXml object which will be used to process
        // each artist folder individually - this is a nice strategy
        // for keeping things neat and contained.
        ofXml artist;
        artist.addChild("ARTIST");
        artist.setTo("ARTIST");
        artist.addValue("artist_name",artist_name);
        
        // create a local ofDirectory file, which will be used to process
        // each album directory individually
        ofDirectory albumDir;
        albumDir.open(rootMusicDir.getPath(i));
        albumDir.listDir();
        // create our first nested loop, to iterate through the album directory
        for (int j = 0; j < albumDir.size(); j++)
        {
            string album_name = albumDir.getName(j);
            
            // set the artist xml object to the root note ("ARTIST")
            // using "//" tells the ofXml object to search from the root
            artist.setTo("//ARTIST");
            artist.addChild("ALBUMS");
            artist.setTo("ALBUMS");
            artist.addChild("ALBUM");
            
            // because we might encounter multiple albums for a single artist
            // we need to set the ofXml object to the correct one.  ofXml can
            // be sent parameters like this: setTo(ALBUM[O]) - just like an
            // array.  Here we create a local string with the correct album
            // index number that we can then pass to the setTo method
            string albumPathWithIndex = "//ARTIST/ALBUMS/ALBUM[" + ofToString(j) + "]";
            artist.setTo(albumPathWithIndex);
            artist.addValue("album_name",album_name);
            artist.addChild("TRACKS");
            artist.setTo("TRACKS");

            // create a local ofDirectory file, which will be used to iterate
            // through each album directory individually
            ofDirectory trackDir;
            trackDir.open(albumDir.getPath(j));
            trackDir.listDir();
            
            // our final nested loop, to iterate over each track
            for (int k = 0; k < trackDir.size(); k++)
            {
                string track_title = trackDir.getName(k);
                ofXml track;
                track.addChild("TRACK");
                track.setTo("TRACK");
                track.addValue("track_title",track_title);
                string iString = ofToString(i);
                string jString = ofToString(j);
                string kString = ofToString(k);
                string unique_ID = iString+jString+kString;
                track.addValue("uniqueID", unique_ID);
                artist.addXml(track);
            }
        }
        // here we add our local artist ofXml object to our global ofXml object.
        // setting the boolean to true tells ofXml to add the entire artist ofXml
        // object, not just the node we are set to right now
        XML.addXml(artist, true);
    }
    // save our global SML
    XML.save("musicLibrary.xml");
    
}

//--------------------------------------------------------------
void testApp::searchLibrary(string searchTerms, bool artist, bool album, bool track){
    
    // load our XML music library file
    XML.load("musicLibrary.xml");
    
    // initialize our search results xml object
    ofXml searchResultsXML;
    searchResultsXML.clear();
    searchResultsXML.addChild("RESULTS");
    searchResultsXML.setTo("RESULTS");
    
    // take our searchTerms and prep them for the RegularExpression
    // more specifically, by surrounding the searchTerms with the
    // regex word boundary symbol, "\b", we can make sure to match
    // whole words only
    string searchTermsPrepped;
    searchTermsPrepped = "\\b" + searchTerms + "\\b";
    cout << "searchTermsPrepped is " << searchTermsPrepped << endl;
    RegularExpression RegEx_searchTerms(searchTermsPrepped, RegularExpression::RE_CASELESS);
    RegularExpression::Match mtch;
    
    // perform our search(es)
    
    if (artist)
    {
        // SEARCH FOR ARTISTS

        
        XML.setTo("//LIBRARY/ARTIST[0]");
        do
        {
            XML.setTo("artist_name");

            string artist_name = XML.getValue();
            //Match myMatch;
            int match = RegEx_searchTerms.match(artist_name, mtch);
            if (match>0)
            {
                XML.setTo("../ALBUMS/ALBUM[0]");
                do
                {
                    XML.setTo("album_name");
                    string album_name = XML.getValue();
                    XML.setTo("../TRACKS/TRACK");
                    do
                    {
                        XML.setTo("track_title");
                        string track_title = XML.getValue();
                        XML.setTo("../uniqueID");
                        string unique_ID = XML.getValue();
                        
                        string pathToTrack = pathToRoot + artist_name + "/" + album_name + "/" + track_title;
                                            
                        ofXml result;
                        result.addChild("RESULT");
                        result.setTo("RESULT");
                        result.addValue("artist_name", artist_name);
                        result.addValue("album_name", album_name);
                        result.addValue("track_title", track_title);
                        result.addValue("uniqueID", unique_ID);
                        result.addValue("path", pathToTrack);
                        searchResultsXML.setTo("//RESULTS");
                        searchResultsXML.addXml(result, true);
                        XML.setTo("../");
                    }
                    while (XML.setToSibling());
                    XML.setTo("../../");
                }
                while (XML.setToSibling());
                XML.setToParent();
            }
            XML.setToParent();
        }
        while (XML.setToSibling());
        searchResultsXML.save("searchResultsXML.xml");
    }
    
    if (album)
    {
        // SEARCH FOR ALBUMS
        XML.setTo("//LIBRARY/ARTIST[0]");
        do
        {
            XML.setTo("artist_name");
            string artist_name = XML.getValue();

            XML.setTo("../ALBUMS/ALBUM[0]");
            do
            {
                XML.setTo("album_name");
                string album_name = XML.getValue();
                int match = RegEx_searchTerms.match(album_name, mtch);
                if (match>0)
                {
                    XML.setTo("../TRACKS/TRACK");
                    do
                    {
                        XML.setTo("track_title");
                        string track_title = XML.getValue();
                        XML.setTo("../uniqueID");
                        string unique_ID = XML.getValue();
                        
                        string pathToTrack = pathToRoot + artist_name + "/" + album_name + "/" + track_title;
                        
                        ofXml result;
                        result.addChild("RESULT");
                        result.setTo("RESULT");
                        result.addValue("artist_name", artist_name);
                        result.addValue("album_name", album_name);
                        result.addValue("track_title", track_title);
                        result.addValue("uniqueID", unique_ID);
                        result.addValue("path", pathToTrack);
                        searchResultsXML.addXml(result, true);
                        XML.setTo("../");
                    }
                    while (XML.setToSibling());
                    
                    XML.setTo("../");
                }
                XML.setTo("../");
                string temp = XML.getName();
            }
            while (XML.setToSibling());
            
            XML.setTo("../../");
            string temp2 = XML.getName();
        }
        while (XML.setToSibling());
        searchResultsXML.save("searchResultsXML.xml");
        
    }
    
    if (track)
    {
        // SEARCH FOR TRACKS
        XML.setTo("//LIBRARY/ARTIST[0]");
        do
        {
            XML.setTo("artist_name");
            string artist_name = XML.getValue();
            
            XML.setTo("../ALBUMS/ALBUM[0]");
            do
            {
                XML.setTo("album_name");
                string album_name = XML.getValue();

                XML.setTo("../TRACKS/TRACK");
                // BEGIN DO STATEMENT
                do
                {
                    XML.setTo("track_title");
                    string track_title = XML.getValue();
                    
                    int match = RegEx_searchTerms.match(track_title, mtch);
                    if (match>0)
                    {
                        XML.setTo("../uniqueID");
                        string unique_ID = XML.getValue();
                        
                        string pathToTrack = pathToRoot + artist_name + "/" + album_name + "/" + track_title;
                        
                        ofXml result;
                        result.addChild("RESULT");
                        result.setTo("RESULT");
                        result.addValue("artist_name", artist_name);
                        result.addValue("album_name", album_name);
                        result.addValue("track_title", track_title);
                        result.addValue("uniqueID", unique_ID);
                        result.addValue("path", pathToTrack);
                        searchResultsXML.addXml(result, true);
                    }
                    XML.setTo("../");
                }
                while (XML.setToSibling());
                // END DO STATEMENT
                
                XML.setTo("../../");
                string temp = XML.getName();
            }
            while (XML.setToSibling());
            
            XML.setTo("../../");
            string temp2 = XML.getName();
        }
        while (XML.setToSibling());
        searchResultsXML.save("searchResultsXML.xml");
    }
    
// locate and remove repeated search results
    
    searchResultsXML.setTo("//RESULTS");
    int numChildren = searchResultsXML.getNumChildren();
    
    for (int i = 0; i < numChildren; i++)
    {
        // we need to string together a string with our result index
        // this is a bit clunkier to do than using a while / do loop
        // but in this case is better because we need to keep track
        // of where in the index we are
        string uniqueIDResultPath = "//RESULTS/RESULT[" + ofToString(i) + "]/uniqueID";
        searchResultsXML.setTo(uniqueIDResultPath);
        
        // because we are reading a value from the xml object, the uniqueID
        // will be returned to us as a string
        string uniqueID = searchResultsXML.getValue();
        
        // now we need to compare this uniqueID to each subsequent
        // uniqueID in our search result file
        
        // we start with the next item in the index
        int j = i+1;
        // then iterate from that next item (now j) to the end of our list
        while (j < numChildren)
        {
            string uniqueIDToComparePath = "//RESULTS/RESULT[" + ofToString(j) + "]/uniqueID";
            string resultToComparePath = "//RESULTS/RESULT[" + ofToString(j) + "]";
            
            searchResultsXML.setTo(uniqueIDToComparePath);
            string uniqueIDToCompare = searchResultsXML.getValue();
            if (uniqueID == uniqueIDToCompare)
            {
                searchResultsXML.setTo(resultToComparePath);
                searchResultsXML.remove();
                // we need to take account for the fact that we are removing a search
                // result and adjust our index and numChildren variables accordingly
                numChildren--;
                j--;
            }
            j++;
        }
    }
    searchResultsXML.save("searchResultsXML.xml");
}

