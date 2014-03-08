#include "testApp.h"
#include "Poco/RegularExpression.h"
#include "Poco/String.h"
using Poco::RegularExpression;

//--------------------------------------------------------------
void testApp::setup(){
    
	// Load a CSV File.
	csv.loadFile(ofToDataPath("us-500.csv"));
    
    string out = "";
    
    for (int i = 0; i < csv.numRows-1; i++)
    {
        out += "#";
        out += textProcess(csv.data[i+1][1]);
        out += " ";
        out += textProcess(csv.data[i+1][2]);
        out += "\r";
        out += "Applicant No. " + ofToString(i+1);
        out += "\r";
        out += "\r";
        
        for (int j = 0; j < csv.data[0].size(); j++)
        {
            out += "###" + textProcess(csv.data[0][j]) + "\r";
            out += textProcess(csv.data[i+1][j]);
            out += "\r";
        }
        out += "***";
        out += "\r";
    }
    
    ofBuffer buffer;
    buffer.set(out);
    
    ofFile mdFile;
    if (!mdFile.open("app.md"))
    {
        ofFile mdFile("apps.md", ofFile::ReadWrite, true); //file doesn't exist yet
        mdFile.create(); // now file doesn't exist
    }
    ofBufferToFile("apps.md", buffer);
    
    mdFile.close();
}
//--------------------------------------------------------------
void testApp::update(){
}
//--------------------------------------------------------------
void testApp::draw(){
}
//--------------------------------------------------------------

string testApp::textProcess(string text){
    
    // declare RegEx
    // _COMMA_ and _NEWLINE_ are keywords I replaced "," and "\n" with in the original spreadsheet, since ofxCsv can't handle them
    RegularExpression RE_Comma("_COMMA_");
    RegularExpression RE_NEWLINE("_NEWLINE_");
    // this is a little regex http finder I built myself thank you very much
    RegularExpression RE_HTTP("(http://[^ \n\r\)]+)|(www\.[^ \n\r\)]+)|(https://[^ \n\r\)]+)");
    RegularExpression::Match myMatch;
    
    // declare local vars
    vector<string> extractedLinks;
    extractedLinks.clear();
    
    // begin to process the text
    RE_Comma.subst(text, ",", RegularExpression::RE_GLOBAL);
    RE_NEWLINE.subst(text, " \r", RegularExpression::RE_GLOBAL);
    // once commas and new lines have been replaced, make a copy of the text for use below
    string textCopy = text;
    
    // while there is more than one link in a text block
    while (RE_HTTP.match(textCopy, myMatch) > 0)
    {
        // extract that link, push into a string vector, and delete it in order to move on to the next one
        string extractedLink;
        RE_HTTP.extract(textCopy, extractedLink);
        extractedLinks.push_back(extractedLink);
        RE_HTTP.subst(textCopy, "");
    }
    
    // now replace each link with the correct markdown syntax...
    for (int i = 0; i < extractedLinks.size(); i++)
    {
        // we need to copy the link so we can clean escape special chars in it
        // before placing it into a regex
        //cout << "extracted line is " << extractedLinks[i] << endl;
        string linkRegEx = extractedLinks[i];
        RegularExpression RE_QuestionMark("[\?]");
        RE_QuestionMark.subst(linkRegEx, "\\?"); // I'm actually not sure why I need two slashes here but it works...
        // now that the question marks have been escaped, we put linkRegEx into a RegEx, in order to replace the original
        // link with the correct MD syntax...
        RegularExpression RE_LinkReplace(linkRegEx);
        string substitutedLink = "[" + extractedLinks[i] + "]" + "(" + extractedLinks[i] + ")";
            //cout << "substituted links is" << substitutedLink << endl;
        RE_LinkReplace.subst(text, substitutedLink);
            //cout << "new text is " << text << endl;
    }
    return text;
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
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