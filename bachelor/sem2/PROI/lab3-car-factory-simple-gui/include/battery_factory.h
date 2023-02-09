#ifndef _BATTERY_FACTORY_H_
#define _BATTERY_FACTORY_H_

#include "factory.h"
#include "battery.h"
class BatteryFactory: public Factory{
public:
    Battery* produce();
private:

};

#endif
