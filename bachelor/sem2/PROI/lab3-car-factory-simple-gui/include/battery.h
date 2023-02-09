#ifndef _BATTERY_H_
#define _BATTERY_H_

#include "part.h"
class Battery: public Part{
public:
    std::string getName() { return "Battery"; }
private:

};

#endif
