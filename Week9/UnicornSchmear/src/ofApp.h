#pragma once


#include "ofMain.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);

    ofMesh mesh;
    ofPolyline polyline;

    bool drawVertexIndicies;

    std::size_t maxPoints;

    bool useAlphaImage;

    ofImage image;
    ofImage alphaImage;
};
