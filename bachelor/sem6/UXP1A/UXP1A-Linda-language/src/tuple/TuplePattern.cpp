#include "../../include/tuple/TuplePattern.h"
#include <cstring>
#include <sstream>

bool TupleElementPattern::checkIfMatch(const TupleElement& tupleElement) const {
    if (tupleElement.getType() != this->valueType) {
        return false;
    }

    if (this->matchOperatorType == WHATEVER) {
        return true;
    }
    variant pattern = this->valueToCompare;
    MatchOperatorType op = this->matchOperatorType;
    variant elemValue = tupleElement.getValue();
    switch (this->valueType) {
        case INT:
            return TupleElementPattern::compareInts(pattern, op, elemValue);
        case FLOAT:
            return TupleElementPattern::compareFloats(pattern, op, elemValue);
        case STRING:
            return TupleElementPattern::compareStrings(pattern, op, elemValue);
    }
    return false;
}

std::string TupleElementPattern::serialize() const {
    std::stringstream buffer;
    ValueType type = this->valueType;
    buffer << type << Separator;
    buffer << this->matchOperatorType << Separator;
    if (this->matchOperatorType == WHATEVER) {
        return buffer.str();//do not serialize value
    }

    if (type == INT)
        buffer << std::get<int>(this->valueToCompare);
    else if (type == FLOAT)
        buffer << std::get<float>(this->valueToCompare);
    else if (type == STRING)
        buffer << std::get<std::string>(this->valueToCompare);
    else
        throw std::runtime_error("Invalid valueType in TupleElementPattern serialization!");
    buffer << Separator;
    return buffer.str();
}

TupleElementPattern TupleElementPattern::deserialize(std::string &content) {
    std::string utilStr = SerializationUtils::getNextElementAndErase(content);
    auto type = (ValueType) std::stoi(utilStr);
    utilStr = SerializationUtils::getNextElementAndErase(content);
    auto matchOperator = (MatchOperatorType) std::stoi(utilStr);

    if (type == FLOAT && matchOperator == EQUAL) {
        throw std::runtime_error("Float-pattern does not have '==' operator!");
    }

    if (matchOperator == WHATEVER) {
        return TupleElementPattern(type, matchOperator, "");
    }

    utilStr = SerializationUtils::getNextElementAndErase(content);
    if (type == INT) {
        int value = std::stoi(utilStr);
        return TupleElementPattern(type, matchOperator, value);
    } else if (type == FLOAT) {
        float value = std::stof(utilStr);
        return TupleElementPattern(type, matchOperator, value);
    } else if (type == STRING) {
        return TupleElementPattern(type, matchOperator, utilStr);
    } else {
        throw std::runtime_error("Invalid valueType in TuplePatternElement deserialization!");
    }
}

TupleElementPattern::TupleElementPattern(std::string patternElementString) {
    std::string typeStr = SerializationUtils::getNextElementAndErase(patternElementString, ':');
    if (typeStr == "integer") {
        this->valueType = INT;
    } else if (typeStr == "float") {
        this->valueType = FLOAT;
    } else if (typeStr == "string") {
        this->valueType = STRING;
    } else {
        throw std::runtime_error("Invalid pattern string - type");
    }

    std::string operatorStr = patternElementString.substr(0, std::min<size_t>(2, patternElementString.size()));

    if (operatorStr == "*") {
        this->matchOperatorType = WHATEVER;
        this->valueToCompare = "";//in order to not throw exception while printing
    } else {
        if (SerializationUtils::doubleChars.count(operatorStr) != 0) {
            this->matchOperatorType = SerializationUtils::doubleChars[operatorStr];
        } else {
            operatorStr = operatorStr.substr(0, 1);
            if (SerializationUtils::singleChars.count(operatorStr) != 0) {
                this->matchOperatorType = SerializationUtils::singleChars[operatorStr];
            } else {
                throw std::runtime_error("Invalid pattern string - operator");
            }
        }

        patternElementString.erase(0, operatorStr.size());
        if (this->valueType == INT) {
            this->valueToCompare = std::stoi(patternElementString);
        } else if (this->valueType == FLOAT) {
            this->valueToCompare = std::stof(patternElementString);
        } else {
            this->valueToCompare = std::move(patternElementString);
        }
    }
}
bool TupleElementPattern::compareInts(variant pattern, MatchOperatorType op, variant tupleElement) {
    int patternValue = std::get<int>(pattern);
    int tupleValue = std::get<int>(tupleElement);

    switch (op) {
        case EQUAL:
            return tupleValue == patternValue;
        case GREATER:
            return tupleValue > patternValue;
        case GREATER_EQUAL:
            return tupleValue >= patternValue;
        case LESS:
            return tupleValue < patternValue;
        case LESS_EQUAL:
            return tupleValue <= patternValue;
        default:
            throw std::runtime_error("Invalid operator while comparing ints!");
    }
}

bool TupleElementPattern::compareFloats(variant pattern, MatchOperatorType op, variant tupleElement) {
    float patternValue = std::get<float>(pattern);
    float tupleValue = std::get<float>(tupleElement);

    switch (op) {
        case EQUAL:
            throw std::runtime_error("Float-pattern should not have '==' operator!");
        case GREATER:
            return tupleValue > patternValue;
        case GREATER_EQUAL:
            return tupleValue >= patternValue;
        case LESS:
            return tupleValue < patternValue;
        case LESS_EQUAL:
            return tupleValue <= patternValue;
        default:
            throw std::runtime_error("Invalid operator while comparing floats!");
    }
}

bool TupleElementPattern::compareStrings(variant pattern, MatchOperatorType op, variant tupleElement) {
    std::string patternValue = std::get<std::string>(pattern);
    std::string tupleValue = std::get<std::string>(tupleElement);

    int result = patternValue.compare(tupleValue);
    return TupleElementPattern::compareInts(result, op, 0);//TODO: albo w odwrotnej kolejnosci, już mi się przed oczami miesza
}

bool TuplePattern::checkIfMatch(const Tuple& tuple) const {
    int noOfElements = this->getNumberOfElements();
    if (tuple.getNumberOfElements() != noOfElements) {
        return false;
    }

    for (int i = 0; i < noOfElements; ++i) {
        if (!this->elementPatterns[i].checkIfMatch(tuple.getElement(i))) {
            return false;
        }
    }

    return true;
}

char *TuplePattern::serialize() const {
    std::string serialized;
    for (auto &pattern : this->elementPatterns) {
        serialized += pattern.serialize();
    }

    if (serialized.size() > MAX_SIZE_IN_BYTES) {//TODO: zostawiamy to?
        throw std::runtime_error("Too many bytes after TuplePattern serialization!");
    }
    char *bytes = new char[serialized.size()];
    strcpy(bytes, serialized.c_str());
    return bytes;
}

TuplePattern TuplePattern::deserialize(char *serialized) {
    std::string str(serialized);

    std::vector<TupleElementPattern> elementPatterns;
    while (!str.empty()) {
        TupleElementPattern t2 = TupleElementPattern::deserialize(str);
        elementPatterns.emplace_back(t2);
    }
    return TuplePattern(std::move(elementPatterns));
}

TuplePattern::TuplePattern(std::string patternString) {
    /*
     * Examples of correct initialize strings:
     * 1. "string:==1; float:*; integer:<=-15"
     * 2. "float:==0.123; integer:*; string:==abcd"
     *
     * Rules:
     * 1. <Type> ":" <Operator> <Value>
     *      -if '*' operator is given, then there should be no value!
     * 2. Colon ':' after <Type> is crucial!
     * 3. Strings are without '"' signs around them
     * 4. No comas ',' and colons ':' are allowed if string values!
     *      - i.e. "ab;das:" is invalid!
     * */
    while (!patternString.empty()) {
        std::string elementPatternStr = SerializationUtils::getNextElementAndErase(patternString, ';');
        while (elementPatternStr[0] == ' ') {//get rid of spaces after coma
            elementPatternStr.erase(0, 1);
        }
        this->elementPatterns.emplace_back(TupleElementPattern(elementPatternStr));
    }
}
std::optional<Tuple> TuplePattern::findMatching(const std::vector<Tuple> &tuples) {
    for( const auto &it : tuples){
        if(checkIfMatch(it))
            return it;
    }
    return std::nullopt;
}

std::optional<Tuple> TuplePattern::deleteMatching(std::vector<Tuple> &tuples) {
    for( auto it = tuples.begin(); it != tuples.end(); ++it ){
        if(checkIfMatch(*it)) {
            Tuple tuple = *it;
            tuples.erase(it);
            return tuple;
        }
    }
    return std::nullopt;
}
