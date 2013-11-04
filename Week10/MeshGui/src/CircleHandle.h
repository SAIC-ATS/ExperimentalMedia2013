#include "BaseHandle.h"


class CircleHandle: public BaseHandle
{
public:
    typedef std::shared_ptr<CircleHandle> SharedPtr; // a typedef to make things a little easier

    CircleHandle(); // constructor (ctor)
    CircleHandle(const ofRectangle& rectangle); // constructor (ctor)

    virtual ~CircleHandle(); // destructor (dtor)

    virtual void update();
    virtual void draw();

    virtual bool hitTest(const ofVec2f& mouse);

    float angle;
    float angleRate;

    float pulse;
    float pulseRate;

};