#ifndef UXP1A_LINDA_LINDA_H
#define UXP1A_LINDA_LINDA_H

#include "../tuple/Tuple.h"
#include "../tuple/TuplePattern.h"


void linda_output(const Tuple& tuple);
std::optional<Tuple> linda_read(const TuplePattern& pattern, time_t timeout); //milliseconds
std::optional<Tuple> linda_input(const TuplePattern& pattern, time_t timeout);

#endif//UXP1A_LINDA_LINDA_H
