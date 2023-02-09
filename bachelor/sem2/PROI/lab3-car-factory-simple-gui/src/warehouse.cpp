#include "warehouse.h"

Warehouse::~Warehouse(){
    clearList_( frames_ );
    clearList_( engines_ );
    clearList_( batteries_ );
    clearList_( cars_ );

}

void Warehouse::addFrame( Frame* newFrame ){
    frames_.push_front(newFrame);
    ++numOfFrames_;
}

void Warehouse::addEngine( Engine* newEngine ){
    engines_.push_front(newEngine);
    ++numOfEngines_;
}

void Warehouse::addBattery( Battery* newBattery ){
    batteries_.push_front(newBattery);
    ++numOfBatteries_;
}

void Warehouse::addCar( Car* newCar ){
    cars_.push_front(newCar);
    ++numOfCars_;
}

Frame* Warehouse::getFrame(){
    if( numOfFrames_ > 0 ){
        Frame* frameToGive = frames_.front();
        frames_.pop_front();
        --numOfFrames_;
        return frameToGive;
    }else{
        return nullptr;
    }
}

Engine* Warehouse::getEngine(){
    if( numOfEngines_ > 0 ){
        Engine* engineToGive = engines_.front();
        engines_.pop_front();
        --numOfEngines_;
        return engineToGive;
    }else{
        return nullptr;
    }
}

Battery* Warehouse::getBattery(){
    if( numOfBatteries_ > 0 ){
        Battery* batteryToGive = batteries_.front();
        batteries_.pop_front();
        --numOfBatteries_;
        return batteryToGive;
    }else{
        return nullptr;
    }
}

Car* Warehouse::getCar(){
    if( numOfCars_ > 0 ){
        Car* carToGive = cars_.front();
        cars_.pop_front();
        --numOfCars_;
        return carToGive;
    }else{
        return nullptr;
    }
}

bool Warehouse::enoughPartsToProduceCar(){
    return (numOfFrames_ > 0 && numOfEngines_ > 0 && numOfBatteries_ > 0);
}

template<class T>
void Warehouse::clearList_( std::forward_list<T> listToClear ){
    while( !listToClear.empty() ){
        delete listToClear.front();
        listToClear.pop_front();
    }
}

