//  Created by Abraham Avnisan on 12/8/13.

#include "SearchResult.h"

// some CONSTANT definitions to make
// things a little easier
#define FONTSIZE 12
#define HOVERFONTSIZE 9
#define CHARWIDTH 9

//--------------------------------------------------------------
SearchResult::SearchResult(const int resultCount,
                           const string artistName,
                           const string albumName,
                           const string trackTitle,
                           const string resultPath,
                           const unsigned int uniqueID,
                           const ofRectangle& rectangle):
artistName(artistName),
albumName(albumName),
trackTitle(trackTitle),
resultPath(resultPath),
resultCount(resultCount),
ofRectangle(rectangle),
bgColorEven(159,188,255),
bgColorOdd(223)
{
    // use the vars that have been passed to our CTOR in order
    // to generate the output text for this result
//    outputText = getOutputText(resultCount, artistName, albumName, trackTitle, rectangle);
    outputText = getOutputText();
  
    // we could have done everything we are doing in setup
    // right here in our CTOR, but it's easier on the eyes
    // and brain to move that into its own method
    SearchResult::setup();
}
//--------------------------------------------------------------
SearchResult::~SearchResult()
{
}
//--------------------------------------------------------------
void SearchResult::setup()
{
    resultFont.loadFont("Consolas.ttf", FONTSIZE, true, false, true);
    hoverFont.loadFont("Verdana.ttf", HOVERFONTSIZE, true, false, true);
    
    textXPos = x;
    textYPos = y + FONTSIZE;
    
    // fine tune adjustments for the text X and Y positions
    textYPos += 2;
    textXPos += 2;
}
//--------------------------------------------------------------
void SearchResult::draw()
{
    ofPushStyle();
    
    // if resultCount is 0, this is our header text, which we
    // want a white background for
    if (resultCount==0)
    {
        ofSetColor(255);
    }
    // Here we check to see if a row is even or odd, and
    // set the color accordingly, then draw our rect
    else if (resultCount%2==0)
    {
        ofSetColor(bgColorEven);
    }
    else
    {
        ofSetColor(bgColorOdd);
    }
    ofFill();
    ofRect(x,y,width,height);
    
    // Here we draw our outputText to the screen
    ofSetColor(0);
    resultFont.drawString(outputText, textXPos, textYPos);
    
    ofPopStyle();
}
//--------------------------------------------------------------
string SearchResult::getOutputText()
{

    // Declare local vars

    string convertedArtist;
    string convertedAlbum;
    string convertedTrack;
    string outputArtist;
    string outputAlbum;
    string outputTrack;
    
    string outputText;

    float outputWidth;
    float sectionWidth;
    int numCharsPerSection;
    
    sectionWidth = (width - 50)/3;
    numCharsPerSection = ceil(sectionWidth/CHARWIDTH);
    
    // Process our text using out static XMTToText::convert
    // method, which checks for any XML entities ("&apos;" instead of "'")
    // and converts those entities back to "normal" text
    convertedArtist = XMLToText::convert(artistName);
    convertedAlbum = XMLToText::convert(albumName);
    convertedTrack = XMLToText::convert(trackTitle);
    
    
    // Now we check the length of our converted texts and format
    // them for output accordingly.  If the string is longer than
    // the space available, it is truncated.  If it's longer,
    // blank spaces are added to it.  This allows all our results
    // to line up nicely in the result pane.
    
    // by pushing our converted strings and output strings into two
    // vectors, we can do this all with one loop
    vector<string> convertedStrings;
    convertedStrings.push_back(convertedArtist);
    convertedStrings.push_back(convertedAlbum);
    convertedStrings.push_back(convertedTrack);
    
    vector<string> outputStrings;
    for (int i = 0; i < convertedStrings.size(); i++)
    {
        string myString;
        outputStrings.push_back(myString);
    }

    for (int i = 0; i < convertedStrings.size(); i++)
    {
        // check to see of the convertedString exceeds teh section length
        if (convertedStrings[i].length() > numCharsPerSection-3)
        {
            for (int j = 0; j < numCharsPerSection-3; j++)
            {
                // the std::string.substr method allows us to iterate
                // over our string one character at a time, up to
                // the numCharsPerSection - 3.  We substract 3 so that
                // we leave room for "..." at the end of the string
                outputStrings[i] = convertedStrings[i].substr(0, j);
            }
            outputStrings[i] += "...";
        }
        // if the convertedString is less characters than the section
        // length, we'll format it by adding spaces to the end of it
        else
        {
            outputStrings[i] = convertedStrings[i];
            int numSpaces = numCharsPerSection - convertedStrings[i].length();
            for (int j = 0; j < numSpaces-1; j++)
            {
                outputStrings[i] += " ";
            }
        }
    }
    
    // here we format the result count, adding a 0 in front
    // of single digit results
    string resultCountString;
    
    // if resultCount is 0, this is our header text
    if (resultCount==0)
    {
        resultCountString = " # ";
    }
    else if (resultCount < 10)
    {
        resultCountString = "00" + ofToString(resultCount);
    }
    else if (resultCount < 100)
    {
        resultCountString = "0" + ofToString(resultCount);
    }
    else
    {
        resultCountString = ofToString(resultCount);
    }
    
    // We are now finally ready to string together the text for output
    // let's pull the strings out of our outputStrings vector and assign
    // them to our output vars
    outputArtist = outputStrings[0];
    outputAlbum = outputStrings[1];
    outputTrack = outputStrings[2];
    
    outputText = resultCountString + "|" + outputTrack + "|" + outputAlbum + "|" + outputArtist;
    return outputText;
}
//--------------------------------------------------------------
void SearchResult::hoverResults(const ofVec2f mouse){
    if (inside(mouse))
    {
        
        // First we will strip XML entities and add "labels" in front of each
        // string we want to print in the hover box
        string convertedArtist = "ARTIST: " + XMLToText::convert(artistName);
        string convertedAlbum = "ALBUM: " + XMLToText::convert(albumName);
        string convertedTrack = "TRACK: " + XMLToText::convert(trackTitle);
        string convertedPath = "PATH: " + XMLToText::convert(resultPath);
    
        // Now we'll take those first three of those string and push them back
        // into a string vector (we'll deal with the path on its own in just a bit)
        vector<string> convertedStrings;
        convertedStrings.push_back(convertedArtist);
        convertedStrings.push_back(convertedAlbum);
        convertedStrings.push_back(convertedTrack);
        
        // let's get the width in pixels AND the number of chars
        // of the longest of these first three strings - we'll use
        // that to determine the width of our hoverRect and how
        // long each segment of our path should be
        float hoverWidth;
        int hoverWidthCharLength;
        for (int i = 0; i < convertedStrings.size(); i++)
        {
            float stringWidthCompare;
            stringWidthCompare = hoverFont.stringWidth(convertedStrings[i]);
            if (stringWidthCompare > hoverWidth)
            {
                hoverWidth = stringWidthCompare;
                hoverWidthCharLength = convertedStrings[i].length();
            }
        }

        // the path tends to be quite long, so we need to check how long it is
        // and break it up into multiple lines if necessarry

        int pathSegmentLength = hoverWidthCharLength;
        int pathLength = convertedPath.length();
        int remainder = pathLength % pathSegmentLength;
        
        if (pathLength > pathSegmentLength)
        {
            int numSegments = ceil((float)pathLength/pathSegmentLength);
            for (int i = 0; i < numSegments; i++)
            {
                string segmentString;
                
                // we are going to keep track of where to start pulling substrings
                // from our convertedPath, and how long each substr should be
                int substrIndex = i * pathSegmentLength;
                int substrLength;
                if (i+1 < numSegments)
                {
                    substrLength = pathSegmentLength;
   
                }
                else
                {
                    substrLength = pathSegmentLength - remainder;
                }
                // here we actually do the pulling from the longer string, store
                // what we get in out segmentString string, then do a push_back
                // into our convertedStrings vector
                segmentString = convertedPath.substr(substrIndex, substrLength);
                convertedStrings.push_back(segmentString);
            }
        }
        // if our path happens to be less characters than the longest of the other
        // strings, we'll just print the converted path all in one line
        else
        {
            convertedStrings.push_back(convertedPath);
        }

        // Now we can begin actually drawing stuff to the screen
        ofPushStyle();
        ofTranslate(mouse);  // make the mouse position our new (0,0);
        
        // calculate rectHeight (we will be printing as many lines as there are
        // items in our convertedStrings vector)
        float hoverHeight = HOVERFONTSIZE * convertedStrings.size();
        
        int xMargin = 6;
        int yMargin = 4;
        hoverWidth += (xMargin*2);
        hoverHeight += (yMargin*2) * convertedStrings.size(); // a little extra for margin
        ofRectangle hoverRect(0, 0, hoverWidth, hoverHeight);
        
        // draw the inside of our hover rect
        ofColor hoverBackground(255,251,133, 230);
        ofSetColor(hoverBackground);
        ofFill();
        ofRect(hoverRect);
        
        // draw the outline of our hoverRect
        ofSetColor(150);
        ofNoFill();
        ofRect(hoverRect);
        
        // draw our full result text
        ofSetColor(0);
        for (int i = 0; i < convertedStrings.size(); i++)
        {
            float yPos = (i+1) * (HOVERFONTSIZE + yMargin*1.5);
            hoverFont.drawString(convertedStrings[i], xMargin, yPos);
        }
        
        ofPopStyle();
    }
}












