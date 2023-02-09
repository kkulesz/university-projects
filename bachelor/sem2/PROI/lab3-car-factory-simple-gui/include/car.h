#ifndef _CAR_H_
#define _CAR_H_

#include "frame.h"
#include "engine.h"
#include "battery.h"

class Car{
public:
    Car(Frame*, Engine*, Battery*);
    ~Car();
private:
    Frame* itsFrame_;
    Engine* itsEngine_;
    Battery* itsBattery_;
};

#endif
