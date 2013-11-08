#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofEnableAlphaBlending();

    image.loadImage("image.png");

    theBoxBeingDragged.reset(); // this makes sure it is empty

    CircleHandle::SharedPtr circleHandle;
    ofRectangle rectangle;

    int width = 40;
    int height = width;

    // make four handles
    rectangle.setFromCenter(100,100,width,height);
    boxes.push_back(CircleHandle::SharedPtr(new CircleHandle(rectangle)));

    rectangle.setFromCenter(400,100,width,height);
    boxes.push_back(CircleHandle::SharedPtr(new CircleHandle(rectangle)));

    rectangle.setFromCenter(400,400,width,height);
    boxes.push_back(CircleHandle::SharedPtr(new CircleHandle(rectangle)));

    rectangle.setFromCenter(100,400,width,height);
    boxes.push_back(CircleHandle::SharedPtr(new CircleHandle(rectangle)));

}

//------------------------------------------------------------------------------
void ofApp::update()
{
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    // create first triangle
    mesh.addVertex(boxes[0]->getPosition());
    mesh.addTexCoord(ofVec2f(0,0));

    mesh.addVertex(boxes[1]->getPosition());
    mesh.addTexCoord(ofVec2f(image.width,0));

    mesh.addVertex(boxes[2]->getPosition());
    mesh.addTexCoord(ofVec2f(image.width,image.height));

    // create second triangle
    mesh.addVertex(boxes[2]->getPosition());
    mesh.addTexCoord(ofVec2f(image.width,image.height));

    mesh.addVertex(boxes[3]->getPosition());
    mesh.addTexCoord(ofVec2f(0,image.height));

    mesh.addVertex(boxes[0]->getPosition());
    mesh.addTexCoord(ofVec2f(0,0));

    // update the boxes (for pulsing effects, etc)
    for(std::size_t i = 0; i < boxes.size(); ++i)
    {
        boxes[i]->update();
    }
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);

    image.bind(); // bind the image we want to use for our drawing
    mesh.draw();
    image.unbind();

    for(std::size_t i = 0; i < boxes.size(); ++i)
    {
        boxes[i]->draw();
    }
}

//------------------------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
    ofVec2f mouse(x,y);

    for(std::size_t i = 0; i < boxes.size(); ++i)
    {
        boxes[i]->isOver = boxes[i]->hitTest(mouse);
    }
}

//------------------------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    ofVec2f mouse(x,y);

    if(0 != theBoxBeingDragged) // check to see if our shared pointer contains a valid box
    {
        theBoxBeingDragged->setPosition(mouse - boxDragOffset);
    }
}

//------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    ofVec2f mouse(ofGetMouseX(),ofGetMouseY());

    for(std::size_t i = 0; i < boxes.size(); ++i)
    {
        if(boxes[i]->hitTest(mouse))
        {
            boxes[i]->isDragging = true;
            boxes[i]->isOver = true;

            boxDragOffset = mouse - boxes[i]->getPosition();

            theBoxBeingDragged = boxes[i];
            break; // break out of the for loop, you can't drag more than one at a time
        }
    }
}

//------------------------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    if(0 != theBoxBeingDragged) // check to see if our shared pointer contains a valid box
    {
        theBoxBeingDragged->isDragging = false;
        theBoxBeingDragged.reset(); // clear our pointer
    }
}
