// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofBackground(0);

    grabber.initGrabber(1280,720);

    brightnessThreshold = 127;

    barHeight = 50;
    historyBarWidth = ofGetWidth() - barHeight;

    isHigh = false;
    lastCrossing = 0;
    
    dtDot    = 75;
    dtDash   = dtDot * 3;

    dtPauseCode   = dtDot;
    dtPauseLetter = dtDot * 3;
    dtPauseWord   = dtDot * 7;
    dtPausePhrase = dtDot * 14;

    // sound!

    // 2 output channels,
	// 0 input channels
	// 22050 samples per second
	// 512 samples per buffer
	// 4 num buffers (latency)

	int bufferSize		= 512;
	sampleRate 			= 44100;
	volume				= 0;
	targetVolume        = 0;
    frequency           = 440;
    phase               = 0;

	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);
    
	soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);

    soundStream.start();

    makeMorseMap();
    
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    unsigned long long now = ofGetElapsedTimeMillis();

    grabber.update();

    if(grabber.isFrameNew())
    {
        ofPixelsRef pixels = grabber.getPixelsRef();
        sensorColorRaw = pixels.getColor(sensor.x,sensor.y);
        sensorColorBrightness = sensorColorRaw.getBrightness();

        brightnessHistory.push_back(sensorColorBrightness);

        if(brightnessHistory.size() > 1)
        {
            float currentValue = brightnessHistory[brightnessHistory.size()-1];
            float lastValue = brightnessHistory[brightnessHistory.size()-2];

            if(currentValue < brightnessThreshold && lastValue >= brightnessThreshold)
            {
                unsigned long long highDuration = now - lastCrossing;

                // was it a dot or a dash?
                // because of the camera's after image, we reverse the search
                if(highDuration > dtDash)
                {
                    letterBuffer += "-";
                }
                else
                {
                    letterBuffer += ".";
                }

                isHigh = false;
                lastCrossing = now;
            }
            else if(currentValue >= brightnessThreshold && lastValue < brightnessThreshold)
            {
                unsigned long long lowDuration = now - lastCrossing;

                if(lowDuration < dtPauseLetter)
                {
                    // inside the word
                }
                else if(lowDuration < dtPauseWord)
                {
                    std::string letter = morseDecode(letterBuffer);
                    resolvedLetters.push_back(TextPosition(letter,0));
                    wordBuffer += letter;
                    letterBuffer.clear();
                }
                else
                {
                    std::string letter = morseDecode(letterBuffer);
                    resolvedLetters.push_back(TextPosition(letter,0));
                    wordBuffer += letter;
                    letterBuffer.clear();

                    resolvedWords.push_back(TextPosition(wordBuffer,0));
                    wordBuffer.clear();
                }

                isHigh = true;
                lastCrossing = now;
            }
            else
            {
                // not interested in this point.
            }
        }

        volume = isHigh ? 1 : 0;

        while(brightnessHistory.size() > historyBarWidth)
        {
            brightnessHistory.pop_front();
        }

        std::vector<TextPosition>::iterator letterIter = resolvedLetters.begin();
        
        while (letterIter != resolvedLetters.end())
        {
            if ((*letterIter).x > ofGetWidth())
            {
                cout << "Ersing resolved letter " << endl;
                letterIter = resolvedLetters.erase(letterIter);
            }
            else
            {
                (*letterIter).x++;
                ++letterIter;
            }
        }

        std::vector<TextPosition>::iterator wordIter = resolvedWords.begin();

        while (wordIter != resolvedWords.end())
        {
            if ((*wordIter).x > ofGetWidth())
            {
                wordIter = resolvedWords.erase(wordIter);
            }
            else
            {
                (*wordIter).x++;
                ++wordIter;
            }
        }

    }
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    ofFill();
    ofSetColor(255);
    ofSetRectMode(OF_RECTMODE_CORNER);
    grabber.draw(0,0);

    ofSetColor(255);
    ofNoFill();

    ofSetRectMode(OF_RECTMODE_CENTER);
    ofCircle(sensor,5);

    ofLine(sensor.x+3,sensor.y-3,sensor.x+20,sensor.y-20);

    ofFill();
    ofSetColor(sensorColorRaw);
    ofRect(sensor.x+20,sensor.y-20,20,20);
    ofFill();
    ofSetColor(sensorColorBrightness);
    ofRect(sensor.x+20+20,sensor.y-20,20,20);

    drawAnalysisBar();
}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch(key)
    {
            case '[':
            brightnessThreshold -= 5;
            break;
            case ']':
            brightnessThreshold += 5;
            break;
    }
}

//------------------------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    sensor = ofVec2f(x,y);
}

//------------------------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    historyBarWidth = ofGetWidth() - barHeight;
}

//------------------------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//------------------------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

//------------------------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){

	// sin (n) seems to have trouble when n is very large, so we
	// keep phase in the range of 0-TWO_PI like this:
	while (phase > TWO_PI)
    {
		phase -= TWO_PI;
	}

    for (std::size_t i = 0; i < bufferSize; ++i)
    {
        phase += (frequency / (float) sampleRate) * TWO_PI;;
        float sample = sin(phase);
        lAudio[i] = output[i*nChannels    ] = sample * volume * 0.5;
        rAudio[i] = output[i*nChannels + 1] = sample * volume * 0.5;
    }

}

//------------------------------------------------------------------------------
void ofApp::drawAnalysisBar()
{
    ofPushStyle();


    ofSetRectMode(OF_RECTMODE_CORNER);

    int x = 0;
    int y = ofGetHeight() - barHeight;

    ofPushMatrix();
    ofTranslate(historyBarWidth,y);
    ofFill();
    ofSetColor(sensorColorBrightness);
    ofRect(0,0,barHeight,barHeight);

    ofSetColor(255);
    ofDrawBitmapStringHighlight(letterBuffer,ofPoint(4,-8));

    for(int i = 0; i < resolvedLetters.size(); ++i)
    {
        ofDrawBitmapStringHighlight(resolvedLetters[i].text,ofPoint(-resolvedLetters[i].x,-8));
    }

    for(int i = 0; i < resolvedWords.size(); ++i)
    {
        ofDrawBitmapStringHighlight(resolvedWords[i].text,ofPoint(-resolvedWords[i].x,-30),ofColor(255),ofColor(0));
    }



    ofPopMatrix();

    ofPushMatrix();
    ofTranslate(x,y);
    ofFill();
    ofSetColor(0,80);
    ofRect(0,0,historyBarWidth,barHeight);

    ofSetColor(255,255,0,80);
    float thesholdY = ofMap(brightnessThreshold,0,255,barHeight,0);
    ofLine(0,thesholdY,historyBarWidth,thesholdY);

    ofSetColor(255);

    historyMesh.clear();
    historyMesh.setMode(OF_PRIMITIVE_LINE_STRIP);

    for(std::size_t x = 0; x < brightnessHistory.size(); ++x)
    {
        float scaledValue = ofMap(brightnessHistory[x],0,255,barHeight,0);
        historyMesh.addVertex(ofVec2f(x,scaledValue));
        historyMesh.addColor(ofColor(255,brightnessHistory[x] > brightnessThreshold ? 255 : 0));
    }

    ofTranslate(historyBarWidth-brightnessHistory.size(), 0);

    historyMesh.draw();

    ofPopMatrix();

    ofPopStyle();

    

}

//------------------------------------------------------------------------------
void ofApp::makeMorseMap()
{
    morseMap["-----"] = "0";
    morseMap[".----"] = "1";
    morseMap["..---"] = "2";
    morseMap["...--"] = "3";
    morseMap["....-"] = "4";
    morseMap["....."] = "5";
    morseMap["-...."] = "6";
    morseMap["--..."] = "7";
    morseMap["---.."] = "8";
    morseMap["-----"] = "9";
    morseMap[".-"] = "A";
    morseMap["-..."] = "B";
    morseMap["-.-."] = "C";
    morseMap["-.."] = "D";
    morseMap["."] = "E";
    morseMap["..-."] = "F";
    morseMap["--."] = "G";
    morseMap["...."] = "H";
    morseMap[".."] = "I";
    morseMap[".---"] = "J";
    morseMap["-.-"] = "K";
    morseMap[".-.."] = "L";
    morseMap["--"] = "M";
    morseMap["-."] = "N";
    morseMap["---"] = "O";
    morseMap[".--."] = "P";
    morseMap["--.-"] = "Q";
    morseMap[".-."] = "R";
    morseMap["..."] = "S";
    morseMap["-"] = "T";
    morseMap["..-"] = "U";
    morseMap["...-"] = "V";
    morseMap[".--"] = "W";
    morseMap["-..-"] = "X";
    morseMap["-.--"] = "Y";
    morseMap["--.."] = "Z";

}

//------------------------------------------------------------------------------
std::string ofApp::morseDecode(const std::string& morse)
{
    std::map<std::string,std::string>::iterator iter = morseMap.find(morse);

    if(iter != morseMap.end())
    {
        return (*iter).second;
    }
    else
    {
        return "?";
    }
}

