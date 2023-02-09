#ifndef _CAR_FACTORY_H_
#define _CAR_FACTORY_H_

#include "factory.h"
#include "car.h"

class CarFactory: public Factory{
public:
    Car* produce(Frame*, Engine*, Battery*);
private:
};
#endif
