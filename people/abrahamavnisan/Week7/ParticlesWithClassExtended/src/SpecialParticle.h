#pragma once


#include "BaseParticle.h"


class SpecialParticle: public BaseParticle // here we "inherit" from BaseParticle!
{
public:
    SpecialParticle();
    virtual ~SpecialParticle(); // the virtual keyword indicates that an inheritance relationship is present

    // here we override the draw method in our sub class ... which means that this method
    // will be called rather than the base method ...
    virtual void draw(); // the virtual keyword indicates that an inheritance relationship is present

}; // don't forget the semi-colon after your class definition
