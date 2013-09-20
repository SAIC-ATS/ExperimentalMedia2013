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
    // my threshold will determin how close two points have to be to draw
    // a line between them.  In this case, we use 50 pixels.
    threshold = 50;

    // This is usually the same as setting the frameRate to 60 Hz.
    // It prevents image "tearing"
    ofSetVerticalSync(true);

    // We must explicitly enable alpha blending if we want it.
    ofEnableAlphaBlending();

    // Here I call a function to generate my random points.
    generatePoints();
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    // first I create a vector (x,y,z) value for my mouse.
    // I will use this to prevent lines from being drawn around my cursor.
    ofVec3f mouse(ofGetMouseX(),ofGetMouseY());

    // Next I introduce a "jiggle" factor.
    // In this case, I'm just adding a tiny bit of random noise
    // to the x and y positions of each point.  Since I only allow a small
    // random variation and the random numbers are uniformly distributed,
    // they should stay in the same place (approximately) but jiggle a little.
    for(std::size_t i = 0; i < TOTAL_POINTS; ++i)
    {
        float jiggleFactor = 1;

        // here I measure the distance in pixels from the mouse
        // to the current point that I am working with in my array.
        float distance = points[i].distance(mouse);

        // here I scale my "jiggle" factor based on how close
        // the point is to my mouse.  
        if(distance < threshold)
        {
            jiggleFactor = ofMap(distance,0,threshold,100,1);
        }

        points[i].x += ofRandom(-.5,.5) * jiggleFactor;
        points[i].y += ofRandom(-.5,.5) * jiggleFactor;
    }

    // here I clear my ofVboMesh object (the object I use to draw everything
    // really really fast).
    mesh.clear();

    // I set the line mode.  Other possibilities include:

    //        OF_PRIMITIVE_TRIANGLES,
    //        OF_PRIMITIVE_TRIANGLE_STRIP,
    //        OF_PRIMITIVE_TRIANGLE_FAN,
    //        OF_PRIMITIVE_LINES,
    //        OF_PRIMITIVE_LINE_STRIP,
    //        OF_PRIMITIVE_LINE_LOOP,
    //        OF_PRIMITIVE_POINTS

    // Try some.

    mesh.setMode(OF_PRIMITIVE_LINES);

    // Here I cycle through all points with all other points.
    // If the objects are within "threshold" distance, then I draw
    // a line by adding two points to the mesh.  I also set
    // colors for that mesh point pair.  A "gradient" in the line
    // naturally occurs as the graphics card attempts to smoothly
    // transition the color between two points.
    for(size_t i = 0; i < TOTAL_POINTS; ++i)
    {
        for(size_t j = 0; j < TOTAL_POINTS; ++j)
        {
            // I don't compare a point to itself.
            if(i != j)
            {
                float distance = points[i].distance(points[j]);

                if(distance < threshold)
                {
                    float alpha = ofMap(distance, 0, threshold, 1, 0);

                    mesh.addVertex(points[i]);
                    mesh.addColor(ofFloatColor(colors[i],alpha));
                    mesh.addVertex(points[j]);
                    mesh.addColor(ofFloatColor(colors[j],alpha));
                }
            }
        }
    }

}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    // I get fancy and draw a radial gradient here.
    ofBackgroundGradient(ofColor(255,229,200),ofColor(45,34,30));

    // Here I draw my mesh.
    mesh.draw();
}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    // Here I wait for the spacebar ' ' to be pressed.  Whe it is pressed,
    // I generate a new set of randome points.
    if(key == ' ')
    {
        generatePoints();
    }
}

//------------------------------------------------------------------------------
void ofApp::generatePoints()
{
    for(std::size_t i = 0; i < TOTAL_POINTS; ++i)
    {
        float randomX = ofRandom(ofGetWidth());
        float randomY = ofRandom(ofGetHeight());

        points[i] = ofVec2f(randomX,randomY);
        colors[i] = ofColor(255,229,200).lerp(ofColor(45,34,30),ofRandom(1));
    }

}
