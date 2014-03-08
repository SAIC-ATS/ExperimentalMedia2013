#include "testApp.h"

#include "Poco/RegularExpression.h"
#include "Poco/String.h"
using Poco::RegularExpression;
using Poco::trimLeftInPlace;

//--------------------------------------------------------------
void testApp::setup(){
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(50);
    ofDrawBitmapString("press space to select a file in the root dir you would like to process", 10,10);
    ofDrawBitmapString("(there is an example folder in the bin)", 100, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key==' ')
    {
        // *I couldn't figure out how to select a directory,
        //  so resorted to selecting a file in the root dir
        //  I wanted to process - is there a bettery way to
        //  do this?
        
        ofFileDialogResult openDirResult= ofSystemLoadDialog("select a file in the root of dir to process");
        string path = openDirResult.getPath();
        RegularExpression regEx("/*.*/");
        string pathNoFile;
        int n = regEx.extract(path, pathNoFile);
        
        // this method populates namesVec
        // * should the method return namesVec
        //   instead?
        processFolderNames(pathNoFile);
        
        recursiveRename(pathNoFile, subFolderPaths);
        
        // debug loop to make sure namesVec was populated correctly
        //        for (int i = 0; i<namesVec.size(); i++)
        //        {
        //            for (int j = 0; j< namesVec[i].size(); j++)
        //            {
        //                cout << "namesVec[" << i << "][" << j << "] is " << namesVec[i][j] << endl;
        //            }
        //        }
    }
    
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
//--------------------------------------------------------------
void testApp::processFolderNames(string rootDir)
{
    RegularExpression regEx(rootDir);
    
    // I'm looking for folders in the form of "Firstname Lastname 01-01-2013"
    RegularExpression regExValidate("[A-Za-z_]+ [A-Za-z_]+ [0-9]+-[0-9]+-[0-9]+.*");
    
    // Because I know that my folders come consistently in the form Firstname Lastname
    // I can use the regex "^" anchor to restrict my search to the beginning of the
    // string
    RegularExpression regExFirstName("^[A-Za-z_]+");
    
    // Because there is always a space between Firstname and Lastname
    // I can place a space into my regex and be confident it will only
    // match the lastname
    RegularExpression regExLastName(" [A-Za-z_]+");
    
    string tempLast;
    string tempFirst;
    string tempDir;
    
    dir.open(rootDir);
    dir.createDirectory(rootDir+"/RENAMED/");
    dir.listDir();
    dir.sort();
    for (int i = 0; i < dir.size(); i++)
    {
        tempDir = dir.getPath(i);
        
        // strip the path from tempDir, so we can more easily check
        // the folders and files in the directory
        regEx.subst(tempDir, "");
        
        // check to see whether directory contents are what we're looking for
        bool match = regExValidate.match(tempDir);
        
        // if it matches, add it to our array
        if (match)
        {
            subFolderPaths.push_back(tempDir);
            regExFirstName.extract(tempDir, tempFirst);
            firstName.push_back(tempFirst);
            regExLastName.extract(tempDir, tempLast);
            trimLeftInPlace(tempLast);
            lastName.push_back(tempLast);
            //cout << "temp last is " << tempLast << endl;
            match = false;
        }
    }
    namesVec.push_back(lastName);
    namesVec.push_back(firstName);
}
//--------------------------------------------------------------
void testApp::recursiveRename(string rootDir, vector<string> subFolderPaths){
    
    // The folders I'm dealing with have .htm files that I don't care about
    RegularExpression regExHTM("[a-zA-Z_]*.htm");
    
    // declare some local vars
    string newFileName;
    string originalFileName;
    string path;
    string renamePath;
    string extension;
    bool fileAdded;
    ofFile tempFile;
    
    // open each subdirectory in the root directory
    for (int i = 0; i < subFolderPaths.size(); i++)
    {
        path = rootDir+subFolderPaths[i];
        dir.open(path);
        dir.listDir();
        fileAdded = false;
        // iterate over each file in the subdirectory
        for (int j = 0; j < dir.size(); j++)
        {
            originalFileName = dir.getName(j);
            
            // don't process .htm files
            bool match = regExHTM.match(originalFileName);
            if (!match)
            {
                tempFile = dir.getFile(j);
                extension = tempFile.getExtension();
                if (extension != "")
                {
                    newFileName = namesVec[0][i] + "_" + namesVec[1][i] + "." + extension;
                    renamePath = rootDir + "/RENAMED/"+ newFileName;
                    cout << "temp file name is " << newFileName << endl;
                    cout << "renamePath is " << renamePath << endl;
                    tempFile.copyTo(renamePath);
                    filesVec.push_back(dir.getFile(j));
                    fileAdded = true;
                }
            }
        }
        // make sure that at least ONE file is added from each subdirectory
        if (!fileAdded)
        {
            cout << "FILE NOT ADDED IN SUBDIRECTORY WITH INDEX " << i << endl;
            cout << "DOUBLE CHECK THAT FILES ARE IN ORDER BEFORE CONTINUING" << endl;
            return;
        }
    }
}
