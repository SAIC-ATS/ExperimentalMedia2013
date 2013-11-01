#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofEnableAlphaBlending();

    drawVertexIndicies = false;

    image.loadImage("image.png");
    alphaImage.loadImage("image_a.png");

    maxPoints = 100;

    useAlphaImage = false;
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

        float strokeWidth = ofMap(distance,0,100,100,255,true);
        float alpha = ofMap(distance,0,100,200,255,true);

        mesh.addVertex(currentPoint + (normalPoint * strokeWidth));
        mesh.addColor(ofColor(255,alpha));

        mesh.addVertex(currentPoint - (normalPoint * strokeWidth));
        mesh.addColor(ofColor(255,alpha));

        float imageWidth = image.getWidth();
        float imageHeight = image.getHeight();

#ifdef TARGET_OPENGLES
        imageWidth = 1;
        imageHeight = 1;
#endif

        float currentTextureY = ofMap(i,0,polyline.size(),0,imageHeight);

        ofVec2f textureCoordinate0 = ofVec2f(0,currentTextureY);
        ofVec2f textureCoordinate1 = ofVec2f(imageWidth,currentTextureY);

        mesh.addTexCoord(textureCoordinate0);
        mesh.addTexCoord(textureCoordinate1);


    }

    if(useAlphaImage)
    {
        alphaImage.bind();
    }
    else
    {
        image.bind();
    }

    mesh.draw();

    if(useAlphaImage)
    {
        alphaImage.unbind();
    }
    else
    {
        image.unbind();
    }


    if(drawVertexIndicies)
    {
        for(std::size_t i = 0; i < polyline.size(); ++i)
        {
            ofVec2f currentPoint = polyline[i];

            ofDrawBitmapStringHighlight(ofToString(i),currentPoint);

        }
    }

    ofDrawBitmapStringHighlight("Drag mouse.\n(c) to clear\n(space) fullscreen\n(a) alpha-corn", 20,20);
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
    else if('a' == key)
    {
        useAlphaImage = !useAlphaImage;
    }
    else if(' ' == key)
    {
        ofToggleFullscreen();
    }
}

//------------------------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    ofVec2f mouse(x,y);
    polyline.addVertex(mouse);

    while(polyline.size() > maxPoints)
    {
        polyline.getVertices().erase(polyline.getVertices().begin()); // remove oldest
    }
}

//------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    ofVec2f mouse(x,y);
    polyline.addVertex(mouse);

    while(polyline.size() > maxPoints)
    {
        polyline.getVertices().erase(polyline.getVertices().begin()); // remove oldest
    }
}

