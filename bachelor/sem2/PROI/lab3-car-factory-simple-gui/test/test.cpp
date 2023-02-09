#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <typeinfo>
#include "factory_manager.h"

TEST_CASE("parts", "[part]"){
    Frame testFrame;
    Engine testEngine;
    Battery testBattery;
    SECTION("checking getName() of  derivative classes"){
        REQUIRE( testFrame.getName() == "Frame" );
        REQUIRE( testEngine.getName() == "Engine" );
        REQUIRE( testBattery.getName() == "Battery" );
    }
}

TEST_CASE("factories", "[factory], [part]"){
    FrameFactory testFrameFactory;
    EngineFactory testEngineFactory;
    BatteryFactory testBatteryFactory;
    CarFactory testCarFactory;
    SECTION("produce() of all factories"){
        auto testFrame = testFrameFactory.produce();
        REQUIRE( typeid(testFrame) == typeid(Frame*) );

        auto testEngine = testEngineFactory.produce();
        REQUIRE( typeid(testEngine) == typeid(Engine*) );

        auto testBattery = testBatteryFactory.produce();
        REQUIRE( typeid(testBattery) == typeid(Battery*) );

        auto testCar = testCarFactory.produce( testFrame, testEngine, testBattery );
        REQUIRE( typeid(testCar) == typeid(Car*) );
        delete testCar;
    }
}

TEST_CASE("warehouse", "[warehouse], [factory]"){
    FrameFactory testFrameFactory;
    EngineFactory testEngineFactory;
    BatteryFactory testBatteryFactory;
    CarFactory testCarFactory;
    Warehouse testWarehouse;
    SECTION("checking numbers after initialization"){
        REQUIRE( testWarehouse.getFrameNumber() == 0 );
        REQUIRE( testWarehouse.getEngineNumber() == 0 );
        REQUIRE( testWarehouse.getBatteryNumber() == 0 );
        REQUIRE( testWarehouse.getCarNumber() == 0 );
    }

    SECTION(" enoughPartsToProduceCar() with no parts "){
        REQUIRE( testWarehouse.enoughPartsToProduceCar() == false);
    }

    testWarehouse.addFrame( testFrameFactory.produce() );
    SECTION(" enoughPartsToProduceCar() with one part, frame only "){
        REQUIRE( testWarehouse.enoughPartsToProduceCar() == false);
    }

    testWarehouse.addEngine( testEngineFactory.produce() );
    SECTION(" enoughPartsToProduceCar() with two parts, frame and engine "){
        REQUIRE( testWarehouse.enoughPartsToProduceCar() == false);
    }

    testWarehouse.addBattery( testBatteryFactory.produce() );
    SECTION(" enoughPartsToProduceCar() with all parts "){
        REQUIRE( testWarehouse.enoughPartsToProduceCar() == true);
    }

    Frame* newFrame = new Frame;
    Engine* newEngine = new Engine;
    Battery* newBattery = new Battery;
    testWarehouse.addCar( testCarFactory.produce(newFrame, newEngine, newBattery) );
    SECTION("checking getNumber()'s after adding new element"){
        REQUIRE( testWarehouse.getFrameNumber() == 1 );
        REQUIRE( testWarehouse.getEngineNumber() == 1 );
        REQUIRE( testWarehouse.getBatteryNumber() == 1 );
        REQUIRE( testWarehouse.getCarNumber() == 1 );
    }

    newFrame = testWarehouse.getFrame();
    newEngine = testWarehouse.getEngine();
    newBattery = testWarehouse.getBattery();
    Car* newCar = testWarehouse.getCar();
    SECTION("checking getNumer()'s after deleting elements"){
        REQUIRE( testWarehouse.getFrameNumber() == 0 );
        REQUIRE( testWarehouse.getEngineNumber() == 0 );
        REQUIRE( testWarehouse.getBatteryNumber() == 0 );
        REQUIRE( testWarehouse.getCarNumber() == 0 );
    }

    delete newFrame;
    delete newEngine;
    delete newBattery;
    delete newCar;

}


TEST_CASE("factory_manager", "[manager], [factory], [part]"){
    FactoryManager testFactoryManager;

    SECTION(" produce()'s and getNumber()'s "){
        SECTION("after init"){
            REQUIRE( testFactoryManager.getFrameNumber() == 0);
            REQUIRE( testFactoryManager.getEngineNumber() == 0);
            REQUIRE( testFactoryManager.getBatteryNumber() == 0);
            REQUIRE( testFactoryManager.getCarNumber() == 0);
        }

        testFactoryManager.produceFrame();
        SECTION("frame"){
            REQUIRE( testFactoryManager.getFrameNumber() == 1);
        }

        testFactoryManager.produceEngine();
        SECTION("engine"){
            REQUIRE( testFactoryManager.getEngineNumber() == 1);
        }

        testFactoryManager.produceBattery();
        SECTION("battery"){
            REQUIRE( testFactoryManager.getBatteryNumber() == 1);
        }

        SECTION("car"){
            REQUIRE( testFactoryManager.produceCar() );
            REQUIRE( testFactoryManager.getCarNumber() == 1);
        }
    }
}
