#ifndef _ENGINE_FACTORY_H_
#define _ENGINE_FACTORY_H_

#include "factory.h"
#include "engine.h"
class EngineFactory: public Factory{
public:
    Engine* produce();
private:

};

#endif
