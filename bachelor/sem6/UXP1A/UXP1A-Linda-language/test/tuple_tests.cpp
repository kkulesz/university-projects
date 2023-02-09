#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TupleTests
#include "../include/tuple/Tuple.h"
#include "../include/tuple/TuplePattern.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(tuple_tests)

    BOOST_AUTO_TEST_CASE(simple_integer)
    {
        Tuple tuple = Tuple({121});
        char *serializedTuple = tuple.serialize();
        Tuple tuple2 = Tuple::deserialize(serializedTuple);


        BOOST_TEST(tuple.getElementsType(0) == tuple2.getElementsType(0));
        BOOST_TEST(tuple.getNumberOfElements() == tuple2.getNumberOfElements());
    }

    BOOST_AUTO_TEST_CASE(simple_float)
    {
        Tuple tuple = Tuple({121.21f});
        char *serializedTuple = tuple.serialize();
        Tuple tuple2 = Tuple::deserialize(serializedTuple);


        BOOST_TEST(tuple.getElementsType(0) == tuple2.getElementsType(0));
        BOOST_TEST(tuple.getNumberOfElements() == tuple2.getNumberOfElements());
    }

    BOOST_AUTO_TEST_CASE(simple_string)
    {
        Tuple tuple = Tuple({"aaa"});
        char *serializedTuple = tuple.serialize();
        Tuple tuple2 = Tuple::deserialize(serializedTuple);


        BOOST_TEST(tuple.getElementsType(0) == tuple2.getElementsType(0));
        BOOST_TEST(tuple.getNumberOfElements() == tuple2.getNumberOfElements());
    }

    BOOST_AUTO_TEST_CASE(simple_string_and_equal)
    {
        Tuple tuple = Tuple({"aaa"});
        TuplePattern tuplePattern = TuplePattern("string:==aaa");
        char *serializedTuplePattern = tuplePattern.serialize();
        TuplePattern tuplePattern2 = TuplePattern::deserialize(serializedTuplePattern);

        BOOST_TEST(tuplePattern2.checkIfMatch(tuple));
    }

    BOOST_AUTO_TEST_CASE(simple_string_and_whatever)
    {
        Tuple tuple = Tuple({"aaa"});
        TuplePattern tuplePattern = TuplePattern("string:*");
        char *serializedTuplePattern = tuplePattern.serialize();
        TuplePattern tuplePattern2 = TuplePattern::deserialize(serializedTuplePattern);

        BOOST_TEST(tuplePattern2.checkIfMatch(tuple));
    }

    BOOST_AUTO_TEST_CASE(simple_string_and_less)
    {
        Tuple tuple = Tuple({"aaa"});
        TuplePattern tuplePattern = TuplePattern("string:<aab");
        char *serializedTuplePattern = tuplePattern.serialize();
        TuplePattern tuplePattern2 = TuplePattern::deserialize(serializedTuplePattern);

        BOOST_TEST(tuplePattern2.checkIfMatch(tuple));
    }

    BOOST_AUTO_TEST_CASE(simple_float_and_greater)
    {
        Tuple tuple = Tuple({1.21f});
        TuplePattern tuplePattern = TuplePattern("float:>1.0");
        char *serializedTuplePattern = tuplePattern.serialize();
        TuplePattern tuplePattern2 = TuplePattern::deserialize(serializedTuplePattern);

        BOOST_TEST(tuplePattern2.checkIfMatch(tuple));
    }

    BOOST_AUTO_TEST_CASE(simple_float_and_greater_equal)
    {
        Tuple tuple = Tuple({1.21f});
        TuplePattern tuplePattern = TuplePattern("float:>=1.21");
        char *serializedTuplePattern = tuplePattern.serialize();
        TuplePattern tuplePattern2 = TuplePattern::deserialize(serializedTuplePattern);

        BOOST_TEST(tuplePattern2.checkIfMatch(tuple));
    }

    BOOST_AUTO_TEST_CASE(simple_integer_and_less_equal)
    {
        Tuple tuple = Tuple({999});
        TuplePattern tuplePattern = TuplePattern("integer:<=1000");
        char *serializedTuplePattern = tuplePattern.serialize();
        TuplePattern tuplePattern2 = TuplePattern::deserialize(serializedTuplePattern);

        BOOST_TEST(tuplePattern2.checkIfMatch(tuple));
    }

    BOOST_AUTO_TEST_CASE(complex_multiple_elem_tuple_serialization)
    {
        Tuple tuple = Tuple({999, "napis", 10.5f});
        char *serializedTuple = tuple.serialize();
        Tuple tuple2 = Tuple::deserialize(serializedTuple);


        BOOST_TEST(tuple.getElementsType(0) == tuple2.getElementsType(0));
        BOOST_TEST(tuple.getElementsType(1) == tuple2.getElementsType(1));
        BOOST_TEST(tuple.getElementsType(2) == tuple2.getElementsType(2));
        BOOST_TEST(tuple.getNumberOfElements() == tuple2.getNumberOfElements());
    }

    BOOST_AUTO_TEST_CASE(complex_multiple_elem_tuple_pattern_serialization)
    {
        Tuple tuple = Tuple({999, "napis", 10.5f});
        char *serializedTuple = tuple.serialize();
        Tuple tuple2 = Tuple::deserialize(serializedTuple);


        TuplePattern tuplePattern = TuplePattern("integer:<=1000; string:==napis; float:*");
        char *serializedTuplePattern = tuplePattern.serialize();
        TuplePattern tuplePattern2 = TuplePattern::deserialize(serializedTuplePattern);


        BOOST_TEST(tuplePattern2.checkIfMatch(tuple2));
    }


BOOST_AUTO_TEST_SUITE_END();

