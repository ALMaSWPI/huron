#pragma once

#include "generic_component.h"

namespace huron {

class MovingComponent: public GenericComponent{
public:
    virtual bool Move(float val) = 0;
    
    virtual bool Stop() = 0;
};

}