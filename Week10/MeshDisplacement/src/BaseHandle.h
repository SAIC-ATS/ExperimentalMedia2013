#pragma once


#include "ofMain.h"


class BaseHandle
{
public:
    typedef std::shared_ptr<BaseHandle> SharedPtr;

    BaseHandle(); // constructor (ctor)

    BaseHandle(const ofRectangle& rectangle); // constructor (ctor)


    virtual ~BaseHandle(); // destructor (dtor)

    virtual void update();
    virtual void draw();

    ofRectangle box;

    bool isOver;
    bool isDragging;

};

