#include "car.h"

Car::Car( Frame* newFrame ,Engine* newEngine, Battery* newBattery):
    itsFrame_(newFrame),itsEngine_(newEngine), itsBattery_(newBattery){}

Car::~Car(){
    delete itsFrame_;
    delete itsEngine_;
    delete itsBattery_;
}

