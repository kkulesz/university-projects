#ifndef UXP1A_LINDA_CONSTSANDENUMS_H
#define UXP1A_LINDA_CONSTSANDENUMS_H

#include <string>
#include <variant>


enum MatchOperatorType {
    WHATEVER,
    EQUAL,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL
};

// DO NOT CHANGE ORDER OF THESE!
enum ValueType { INT,
                 FLOAT,
                 STRING };

//THESE TOO!
typedef std::variant<int, float, std::string> variant;

const int MAX_SIZE_IN_BYTES = 512;
const char Separator = ';';


#endif//UXP1A_LINDA_CONSTSANDENUMS_H
