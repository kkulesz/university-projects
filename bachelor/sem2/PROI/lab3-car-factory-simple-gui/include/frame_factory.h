#ifndef _FRAME_FACTORY_H_
#define _FRAME_FACTORY_H_

#include "factory.h"
#include "frame.h"
class FrameFactory: public Factory{
public:
    Frame* produce();
private:

};

#endif
