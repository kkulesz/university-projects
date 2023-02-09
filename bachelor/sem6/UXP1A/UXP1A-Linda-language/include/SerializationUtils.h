#ifndef UXP1A_LINDA_SERIALIZATION_UTILS_H
#define UXP1A_LINDA_SERIALIZATION_UTILS_H

#include "ConstsAndEnums.h"
#include <map>

typedef std::map<std::string, MatchOperatorType> stringToOperator;

class SerializationUtils {
public:
    static std::string getNextElementAndErase(std::string &, char separator = Separator);
    static void printVariant(variant);
    static void printType(ValueType);
    static void printOperator(MatchOperatorType);
    static stringToOperator singleChars;
    static stringToOperator doubleChars;
};

#endif//UXP1A_LINDA_SERIALIZATION_UTILS_H
