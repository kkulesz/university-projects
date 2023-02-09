#ifndef _PART_H_
#define _PART_H_

#include <string>

class Part{
public:
    Part() {};
    virtual ~Part() {};
    virtual std::string getName() = 0;
private:

};

#endif
