#pragma once


#include "ofColor.h"
#include "ofGraphics.h"
#include "ofRectangle.h"


class BaseHandle: public ofRectangle
{
public:
    typedef std::shared_ptr<BaseHandle> SharedPtr; // a typedef to make things a little easier

    BaseHandle(); // constructor (ctor)
    BaseHandle(const ofRectangle& rectangle); // constructor (ctor)

    virtual ~BaseHandle(); // destructor (dtor)

    virtual void update();
    virtual void draw();

    virtual bool hitTest(const ofVec2f& mouse);

    bool isOver;
    bool isDragging;

    ofColor color;
    ofColor colorOver;
    ofColor colorDragging;

};

