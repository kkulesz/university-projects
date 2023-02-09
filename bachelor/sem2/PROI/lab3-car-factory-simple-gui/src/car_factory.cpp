#include "car_factory.h"


Car* CarFactory::produce( Frame* newFrame, Engine* newEngine, Battery* newBattery){
    Car* newCar = new Car(newFrame, newEngine, newBattery);
    return newCar;
}
