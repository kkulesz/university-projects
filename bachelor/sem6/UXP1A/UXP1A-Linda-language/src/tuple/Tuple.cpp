#include <cstdarg>
#include <cstring>
#include <iomanip>
#include <iostream>

#include "../../include/SerializationUtils.h"
#include "../../include/tuple/Tuple.h"

/*
 * TODO:jakby komuś chciało sie kiedyś lepiej bawić w serializacje to można wiecej poczytać:
 * 1. https://stackoverflow.com/questions/5609915/best-practice-for-passing-primitive-data-type-in-c-function
 * 2. https://stackoverflow.com/questions/523872/how-do-you-serialize-an-object-in-c
 * 3. https://stackoverflow.com/questions/11415850/c-how-to-serialize-deserialize-objects-without-the-use-of-libraries?rq=1
 * 4. https://stackoverflow.com/questions/1703322/serialize-strings-ints-and-floats-to-character-arrays-for-networking-without-li
 * 5. https://stackoverflow.com/questions/8513202/c-how-to-send-structures-over-socket
 *
 * https://isocpp.org/wiki/faq/serialization#serialize-binary-format
 * */



TupleElement::TupleElement(const variant& val) {
    this->value = val;
    switch (val.index()) {
        case INT:
            this->valueType = INT;
            break;
        case FLOAT:
            this->valueType = FLOAT;
            break;
        case STRING:
            this->valueType = STRING;
            break;
        default:
            throw std::runtime_error("Invalid value in TupleElement constructor!");
    }
}

TupleElement::TupleElement(bool, std::string tupleElementString) {
    std::string typeStr = SerializationUtils::getNextElementAndErase(tupleElementString, ':');
    if (typeStr == "integer") {
        this->valueType = INT;
        this->value = std::stoi(tupleElementString);
    } else if (typeStr == "float") {
        this->valueType = FLOAT;
        this->value = std::stof(tupleElementString);
    } else if (typeStr == "string") {
        this->valueType = STRING;
        this->value = tupleElementString;
    } else {
        throw std::runtime_error("Invalid pattern string - type");
    }
}

std::string TupleElement::serialize() const {
    std::stringstream buffer;
    ValueType type = this->valueType;
    buffer << type << Separator;
    if (type == INT)
        buffer << std::get<int>(this->value);
    else if (type == FLOAT)
        buffer << std::get<float>(this->value);
    else if (type == STRING)
        buffer << std::get<std::string>(this->value);
    else
        throw std::runtime_error("Invalid valueType in TupleElement serialization!");
    buffer << Separator;
    return buffer.str();
}

TupleElement TupleElement::deserialize(std::string &content) {
    std::string utilStr = SerializationUtils::getNextElementAndErase(content);
    auto type = (ValueType) std::stoi(utilStr);

    utilStr = SerializationUtils::getNextElementAndErase(content);
    if (type == INT) {
        int value = std::stoi(utilStr);
        return TupleElement(value);
    } else if (type == FLOAT) {
        float value = std::stof(utilStr);
        return TupleElement(value);
    } else if (type == STRING) {
        return TupleElement(utilStr);
    } else {
        throw std::runtime_error("Invalid valueType in TupleElement deserialization!");
    }
}

Tuple::Tuple(std::vector<variant> vector) {
    int size = vector.size();
    for (int i = 0; i < size; ++i) {
        this->elements.emplace_back(TupleElement(vector[i]));
    }
}

Tuple::Tuple(bool, std::string tupleString) {
    while (!tupleString.empty()) {
        std::string tupleElementString = SerializationUtils::getNextElementAndErase(tupleString, ';');
        while (tupleElementString[0] == ' ') {//get rid of spaces after coma
            tupleElementString.erase(0, 1);
        }
        this->elements.emplace_back(TupleElement(false, tupleElementString));
    }
}

char *Tuple::serialize() const {
    std::string serialized;
    for (auto & element : this->elements) {
        serialized += element.serialize();
    }

    if (serialized.size() > MAX_SIZE_IN_BYTES) {//TODO: zostawiamy to?
        throw std::runtime_error("Too many bytes after Tuple serialization!");
    }
    char *bytes = new char[serialized.size()];
    strcpy(bytes, serialized.c_str());
    return bytes;
}

Tuple Tuple::deserialize(char *serialized) {
    std::string str(serialized);

    std::vector<variant> valuesVector;
    while (!str.empty()) {
        TupleElement t2 = TupleElement::deserialize(str);
        valuesVector.emplace_back(t2.getValue());
    }
    return Tuple(valuesVector);
}


