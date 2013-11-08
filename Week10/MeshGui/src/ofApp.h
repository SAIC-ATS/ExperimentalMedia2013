#pragma once


#include "ofMain.h"
#include "BaseHandle.h"
#include "CircleHandle.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    std::vector<BaseHandle::SharedPtr> boxes;

    BaseHandle::SharedPtr theBoxBeingDragged;
    ofVec2f boxDragOffset;

    ofMesh mesh;

    ofImage image;

};
