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


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

    void generatePoints();

    // I prefer to keep constants (numbers) out of my code.
    // An anonymous enum is one way to do that.
    enum
    {
        TOTAL_POINTS = 1000
    };

    // I create 1000 points total.  Each point has a color and a position.
    // Those colors and positions are stored in the arrays below.

    // this is an array of vector points.  an ofVec3f has x, y and z values
    ofVec3f points[TOTAL_POINTS];

    // this is an array of floating point colors.  an ofFloatColor has
    // high precision r, g, b and alpha values intide.
    ofFloatColor colors[TOTAL_POINTS];

    // A vbo mesh is a really fast way to draw clusters of points.
    ofVboMesh mesh;

    float threshold;

};
