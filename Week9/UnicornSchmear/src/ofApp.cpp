#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofEnableAlphaBlending();

    drawVertexIndicies = false;

    image.loadImage("image.png");
}

//------------------------------------------------------------------------------
void ofApp::update()
{
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white,ofColor::black);

    // clear out my mesh
    mesh.clear();

    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mesh.enableColors();

    for(std::size_t i = 0; i < polyline.size(); ++i)
    {
        ofVec2f currentPoint = polyline[i];

        ofVec2f normalPoint = polyline.getNormalAtIndex(i);

        float distance = 0;

        if(i > 0)
        {
            distance = currentPoint.distance(polyline[i-1]);
        }

        float strokeWidth = ofMap(distance,0,100,50,100,true);
        float alpha = ofMap(distance,0,100,200,255,true);

        mesh.addVertex(currentPoint + (normalPoint * strokeWidth));
        mesh.addColor(ofColor(255,alpha));

        mesh.addVertex(currentPoint - (normalPoint * strokeWidth));
        mesh.addColor(ofColor(255,alpha));

        float imageWidth = image.getWidth();
        float imageHeight = image.getHeight();

        float currentTextureX = 0;

        if(0 == i % 2)
        {
            currentTextureX = imageWidth;
        }

        float currentTextureY = ofMap(i,0,polyline.size(),0,imageHeight);

        ofVec2f textureCoordinate0 = ofVec2f(0,currentTextureY);
        ofVec2f textureCoordinate1 = ofVec2f(imageWidth,currentTextureY);

        mesh.addTexCoord(textureCoordinate0);
        mesh.addTexCoord(textureCoordinate1);


    }

    image.bind();
    mesh.draw();
    image.unbind();


    if(drawVertexIndicies)
    {
        for(std::size_t i = 0; i < polyline.size(); ++i)
        {
            ofVec2f currentPoint = polyline[i];

            ofDrawBitmapStringHighlight(ofToString(i),currentPoint);

        }
    }

    ofDrawBitmapStringHighlight("Drag mouse.\n(c) to clear", 20,20);
}


//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if('c' == key)
    {
        polyline.clear();
    }
    else if('i' == key)
    {
        drawVertexIndicies = !drawVertexIndicies;
    }
}

//------------------------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    ofVec2f mouse(x,y);
    polyline.addVertex(mouse);
}

//------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    ofVec2f mouse(x,y);
    polyline.addVertex(mouse);
}

