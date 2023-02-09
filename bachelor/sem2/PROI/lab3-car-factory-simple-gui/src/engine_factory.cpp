#include "engine_factory.h"

Engine* EngineFactory::produce(){
    Engine* newEngine = new Engine();
    return newEngine;
}
