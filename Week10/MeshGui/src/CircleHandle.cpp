#include "CircleHandle.h"


CircleHandle::CircleHandle():
    BaseHandle(),
    angle(0),
    angleRate(1),
    pulse(0),
    pulseRate(10)
{

}

CircleHandle::CircleHandle(const ofRectangle& rectangle):
    BaseHandle(rectangle),
    angle(0),
    angleRate(1),
    pulse(0),
    pulseRate(10)
{
}

CircleHandle::~CircleHandle()
{
}

void CircleHandle::update()
{
    if(isOver)
    {
        angle += angleRate;
    }

    if(angle > 360 || angle < 0)
    {
        angleRate *= -1;
    }

    pulse += pulseRate;

    if(pulse > 255 || pulse < 0)
    {
        pulseRate *= -1;
    }
}

void CircleHandle::draw()
{
    if(isOver)
    {
        if(isDragging)
        {
            ofSetColor(colorDragging,pulse);
        }
        else
        {
            ofSetColor(colorOver,pulse);
        }
    }
    else
    {
        ofSetColor(color);
    }


    // fill
    ofFill();
    ofEllipse(x,y,width,height);

    if(isOver)
    {
        if(isDragging)
        {
            ofSetColor(colorDragging,255-pulse);
        }
        else
        {
            ofSetColor(colorOver,255-pulse);
        }
    }
    else
    {
        ofSetColor(color);
    }


    // fill
    ofNoFill();
    ofEllipse(x,y,width,height);


    ofPushMatrix();
    ofTranslate(x,y);
    ofRotateZ(angle);
    ofSetColor(255);
    ofLine(0,0,width/2,0);
    ofPopMatrix();
}

bool CircleHandle::hitTest(const ofVec2f& mouse)
{
    float radius = width / 2;
    return mouse.distance(getPosition()) < radius;
}
