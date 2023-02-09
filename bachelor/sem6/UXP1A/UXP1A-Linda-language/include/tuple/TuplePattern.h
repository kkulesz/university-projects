#ifndef UXP1A_LINDA_TUPLE_PATTERN_H
#define UXP1A_LINDA_TUPLE_PATTERN_H

#include "../SerializationUtils.h"
#include "Tuple.h"

class TupleElementPattern {
public:
    TupleElementPattern(std::string);

    bool checkIfMatch(const TupleElement&) const;
    std::string serialize() const ;
    static TupleElementPattern deserialize(std::string &);


    //for debug
    void print() const {
        SerializationUtils::printType(valueType);
        std::cout << ":";
        SerializationUtils::printOperator(matchOperatorType);
        if(matchOperatorType != WHATEVER) {
            SerializationUtils::printVariant(valueToCompare);
        }
    }

private:
    ValueType valueType;
    MatchOperatorType matchOperatorType;
    variant valueToCompare;

    TupleElementPattern(ValueType ty, MatchOperatorType op, variant val) //for deserialization
        : valueType(ty),
          matchOperatorType(op),
          valueToCompare(val){};

    static bool compareInts(variant, MatchOperatorType, variant);
    static bool compareFloats(variant, MatchOperatorType, variant);
    static bool compareStrings(variant, MatchOperatorType, variant);
};

class TuplePattern {
public:
    TuplePattern(std::string);
    std::optional<Tuple> findMatching(const std::vector<Tuple>& tuples);
    std::optional<Tuple> deleteMatching(std::vector<Tuple> &tuples);
    bool checkIfMatch(const Tuple&) const ;
    char *serialize () const ;
    static TuplePattern deserialize(char *);
    [[nodiscard]] int getNumberOfElements() const { return elementPatterns.size(); };

    void print() const {
        int noOfElements = elementPatterns.size();
        std::cout << "Pattern with " << noOfElements << " elements:\n";
        for (int i = 0; i < noOfElements; ++i) {
            std::cout << "\t" << i << ": ";
            elementPatterns[i].print();
            std::cout << std::endl;
        }
    }

private:
    std::vector<TupleElementPattern> elementPatterns;
    TuplePattern(std::vector<TupleElementPattern> vec) : elementPatterns(std::move(vec)){};//for deserialization

};


#endif//UXP1A_LINDA_TUPLE_PATTERN_H
