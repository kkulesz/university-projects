#ifndef _WAREHOUSE_H_
#define _WAREHOUSE_H_

#include <forward_list>
#include "car.h"

class Warehouse{
public:
    Warehouse():numOfFrames_(0), numOfEngines_(0), numOfBatteries_(0), numOfCars_(0){};
    ~Warehouse();

    void addFrame( Frame* );
    void addEngine( Engine* );
    void addBattery( Battery* );
    void addCar( Car* );

    Frame* getFrame();
    Engine* getEngine();
    Battery* getBattery();
    Car* getCar();

    bool enoughPartsToProduceCar();
    int getFrameNumber(){return numOfFrames_; };
    int getEngineNumber(){ return numOfEngines_; };
    int getBatteryNumber(){ return numOfBatteries_; };
    int getCarNumber(){ return numOfCars_; };

private:
    std::forward_list<Frame*> frames_;
    std::forward_list<Engine*> engines_;
    std::forward_list<Battery*> batteries_;
    std::forward_list<Car*> cars_;

    int numOfFrames_;
    int numOfEngines_;
    int numOfBatteries_;
    int numOfCars_;

    template<class T>
    void clearList_( std::forward_list<T>);
};

#endif
