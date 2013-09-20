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


#pragma once


#include "ofMain.h"


class TextPosition
{
public:
    TextPosition(const string& _text, float _x):
        text(_text),
        x(_x)
    {
    }

    std::string text;
    float x;
};

class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void audioOut(float * input, int bufferSize, int nChannels);

    void drawAnalysisBar();

    void makeMorseMap();
    std::string morseDecode(const std::string& morse);

    ofVideoGrabber grabber;

    ofVec2f sensor;
    ofColor sensorColorRaw;
    float sensorColorBrightness;

    float brightnessThreshold;

    bool isHigh;
    unsigned long long lastCrossing;

    unsigned long long dtDot;
    unsigned long long dtDash;
    unsigned long long dtPauseCode;
    unsigned long long dtPauseLetter;
    unsigned long long dtPauseWord;
    unsigned long long dtPausePhrase;

    // analysis bar

    int barHeight;
    int historyBarWidth;

    std::deque<float> brightnessHistory;
    ofVboMesh historyMesh;


    // sound!

    ofSoundStream soundStream;

    float   frequency;
    float   phase;
    int		sampleRate;
    float 	volume;
    float   targetVolume;

    std::vector<float> lAudio;
    std::vector<float> rAudio;

    std::string letterBuffer;
    std::string wordBuffer;

    std::vector<TextPosition> resolvedLetters;
    std::vector<TextPosition> resolvedWords;

    std::map<std::string,std::string> morseMap;
    

};
