#pragma once

#include "ofMain.h"

//I have lots and lots of grading to do this week for my online
//course.  I started building this simple app as a way to
//streamline all that grading / as a way to procrastinate on
//doing all that grading.  It seemed like a good opportunity
//to continue trying to get more fluent in OF, and to play
//around with poco and regex.

//As I was working on it tonight it seemed like it *might* be
//something I could turn into a poco / regEx of tutorial -
//would love your thoughts on that. (If I were to do that,
//I'd tailor the app appropriately.)

//Presently the app is very simple.  I get folders in the form of
//"FirstName LastName Date." The folders contain  an .htm file I
//need to ignore and another file that I need to rename according to
//the first and last name.

//The app does just that, creating a directory called RENAMED in
//the "root", and copying all the files into it. I've commented as
//much as possible (again, with a possible tutorial in mind) and
//indicated questions in the comments with a "*"

//Feel free to run the example.  I've set up an example "root"
//folder in /bin/sampleRoot.  Pressing space and choosing
///bin/sampleRoot/pickMe.txt will have the app run through all its
//methods and rename the appropriate files.


class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    ofDirectory dir;
    ofFileDialogResult openDirResult;
    
    // the method in question - does it make more sense
    // to return a var, or in this case does it not
    // really matter?
    void processFolderNames(string rootDir);
    
    void recursiveRename(string rootDir, vector<string> subFolderPaths);
    
    // *should this vec have a different name than
    //  this, since this is the same name I'm passing
    //  to the above method? (or, if I'm defining this
    //  var globally, do I not need to pass it into my
    //  method at all?)
    vector<string> subFolderPaths;
    
    // multidimensional vec to hold the names
    // *is multidimensional vec overkill here?
    vector<vector<string> > namesVec;
    
    // the name vecs that will be put into namesVec
    // *do I need to declare these here?
    vector<string> lastName;
    vector<string> firstName;
    
    vector<ofFile> filesVec;
    
};
