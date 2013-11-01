#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    for(std::size_t i = 0; i < 10; ++i)
    {
        ofRectangle rectangle(ofRandomWidth(),   // x
                              ofRandomHeight(),  // y
                              ofRandom(10,100),  // width
                              ofRandom(10,100)); // height

        BaseHandle::SharedPtr box = BaseHandle::SharedPtr(new BaseHandle(rectangle));
        boxes.push_back(box);
    }

}

//------------------------------------------------------------------------------
void ofApp::update()
{
    for(std::size_t i = 0; i < boxes.size(); ++i)
    {
        boxes[i]->update();
    }
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    for(std::size_t i = 0; i < boxes.size(); ++i)
    {
        boxes[i]->draw();
    }
}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
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
}

//------------------------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//------------------------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//------------------------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
