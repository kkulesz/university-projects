#include "battery_factory.h"

Battery* BatteryFactory::produce(){
    Battery* newBattery = new Battery();
    return newBattery;
}
