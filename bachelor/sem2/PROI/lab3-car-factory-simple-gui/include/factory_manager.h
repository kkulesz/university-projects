#ifndef _FACTORY_MANAGER_H_
#define _FACTORY_MANAGER_H_

#include "frame_factory.h"
#include "engine_factory.h"
#include "battery_factory.h"
#include "car_factory.h"
#include "warehouse.h"

class FactoryManager{
public:
    void produceFrame();
    void produceEngine();
    void produceBattery();
    void produceAllParts();
    bool produceCar( );//returns true if car is created,which depends on parts availability
    //void getNumbers( int& carNumber, int& frameNumber,int& engineNumber , int& batteryNumber);//changes given ints to number of parts in itsWarehause

    int getEngineNumber(){ return itsWarehouse_.getEngineNumber(); };
    int getFrameNumber(){ return itsWarehouse_.getFrameNumber(); };
    int getBatteryNumber(){ return itsWarehouse_.getBatteryNumber(); };
    int getCarNumber(){ return itsWarehouse_.getCarNumber(); };

private:
    FrameFactory itsFrameFactory_;
    EngineFactory itsEngineFactory_;
    BatteryFactory itsBatteryFactory_;
    CarFactory itsCarFactory_;
    Warehouse itsWarehouse_;

};

#endif
