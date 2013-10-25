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

    std::string makeInfoString();

    std::string getPrimitiveModeString(ofPrimitiveMode mode);

    ofPrimitiveMode currentPrimitiveMode;

    ofMesh mesh;
    bool drawMeshPoints;
    bool drawMeshFill;
    bool drawMeshWireframe;

    ofPolyline polyline;
    bool drawPoly;
    bool drawPolyNormals;
    bool drawPolyTangents;
    bool drawPolyCurves;

    bool drawVertexIndicies;

};
