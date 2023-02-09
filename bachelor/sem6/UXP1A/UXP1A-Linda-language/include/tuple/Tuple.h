#ifndef UXP1A_LINDA_TUPLE_H
#define UXP1A_LINDA_TUPLE_H

#include "../ConstsAndEnums.h"
#include "../SerializationUtils.h"
#include <iostream>
#include <string>
#include <vector>

class TupleElement {
public:
    TupleElement(const variant &);
    TupleElement(bool switcher, std::string);

    [[nodiscard]] variant getValue() const { return value; };
    [[nodiscard]] ValueType getType() const { return valueType; };

    std::string serialize() const;
    static TupleElement deserialize(std::string &);

    //for debug
    void print() {
        SerializationUtils::printType(valueType);
        std::cout<<"=";
        SerializationUtils::printVariant(value);
    }

private:
    variant value;
    ValueType valueType;
};

class Tuple {
public:
    Tuple(std::vector<variant>);
    Tuple(bool switcher, std::string);

    //TODO: jakies sprawdzanie indexu- ale to ewentualnie potem
    [[nodiscard]] TupleElement getElement(int index) const { return elements[index]; };
    [[nodiscard]] variant getElementsValue(int index) const { return elements[index].getValue(); };
    [[nodiscard]] ValueType getElementsType(int index) const { return elements[index].getType(); };
    [[nodiscard]] int getNumberOfElements() const { return elements.size(); };

    char *serialize() const;
    static Tuple deserialize(char *);

    //for debug
    void print() {
        int noOfElements = elements.size();
        std::cout << "Tuple with " << noOfElements << "elements:\n";
        for (int i = 0; i < noOfElements; ++i) {
            std::cout << "\t" << i << ": ";
            elements[i].print();
            std::cout << std::endl;
        }
    }

private:
    std::vector<TupleElement> elements;
};

#endif//UXP1A_LINDA_TUPLE_H
