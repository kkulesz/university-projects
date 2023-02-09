#include "../../include/SerializationUtils.h"
#include "../../include/ConstsAndEnums.h"
#include <iostream>


std::string SerializationUtils::getNextElementAndErase(std::string &str, char separator) {
    auto idx = str.find(separator);
    if (idx == std::string::npos) {//if there is no separator, then return whole string
        idx = str.size();
    }
    std::string contentStr = str.substr(0, idx);
    str.erase(0, idx + 1);
    return std::move(contentStr);
}

void SerializationUtils::printVariant(variant val){
    int valueType = val.index();
    if (valueType == INT)
        std::cout << std::get<int>(val);
    else if (valueType == FLOAT)
        std::cout << std::get<float>(val);
    else if (valueType == STRING)
        std::cout <<"\""<< std::get<std::string>(val)<<"\"";
    else{
        throw std::runtime_error("invalid variant in print");
    }
}

void SerializationUtils::printType(ValueType type){
    if(type == INT){
        std::cout<<"integer";
    }else if(type == FLOAT){
        std::cout<<"float";
    }else if(type == STRING){
        std::cout<<"string";
    }else{
        throw std::runtime_error("invalid type in print");
    }
}
void SerializationUtils::printOperator(MatchOperatorType op){
    if(op == WHATEVER){
        std::cout<<"*";
    }else if(op == GREATER){
        std::cout<<">";
    }else if(op == GREATER_EQUAL){
        std::cout<<">=";
    }else if(op == LESS){
        std::cout<<"<";
    }else if(op == LESS_EQUAL){
        std::cout<<"<=";
    }else if(op == EQUAL){
        std::cout<<"==";
    }else{
        throw std::runtime_error("invalid operator in print");
    }
}

stringToOperator SerializationUtils::doubleChars = {
        {"==", EQUAL},
        {">=", GREATER_EQUAL},
        {"<=", LESS_EQUAL}

};

stringToOperator SerializationUtils::singleChars = {
        {">", GREATER},
        {"<", LESS}};