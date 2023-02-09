#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SocketTests
#include <boost/test/unit_test.hpp>
#include "../include/client/linda.h"
#include <bits/stdc++.h>
#include <chrono>

BOOST_AUTO_TEST_SUITE(socket_tests)

    BOOST_AUTO_TEST_CASE(case_output_string) //10 ("aaa") tuples in server after
    {
        Tuple tuple = Tuple({"aaa"});
        auto start = std::chrono::high_resolution_clock::now();

        std::ios_base::sync_with_stdio(false);
        for( int i = 0; i< 10; ++i)
            linda_output(tuple);
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken =(double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        std::cout << "Time taken by program is : " << std::fixed
             << time_taken << std::setprecision(9);
        std::cout << " sec " << std::endl;
    }

    BOOST_AUTO_TEST_CASE(case_read_string)
    {
        TuplePattern tuplePattern = TuplePattern("string:<aab");
        auto start = std::chrono::high_resolution_clock::now();

        std::ios_base::sync_with_stdio(false);
        for( int i = 0; i< 10; ++i) {
            std::optional<Tuple> t = linda_read(tuplePattern, 1000);
            bool isMatch = tuplePattern.checkIfMatch(*t);
            BOOST_TEST(isMatch);
        }
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken =(double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        std::cout << "Time taken by program is : " << std::fixed
                  << time_taken << std::setprecision(9);
        std::cout << " sec " << std::endl;
    }

    BOOST_AUTO_TEST_CASE(case_input_string)
    {
        TuplePattern tuplePattern = TuplePattern("string:<aab");
        auto start = std::chrono::high_resolution_clock::now();

        std::ios_base::sync_with_stdio(false);
        for( int i = 0; i< 10; ++i) {
            std::optional<Tuple> t = linda_input(tuplePattern, 1000);
            bool isMatch = tuplePattern.checkIfMatch(*t);
            BOOST_TEST(isMatch);
        }
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        std::cout << "Time taken by program is : " << std::fixed
                  << time_taken << std::setprecision(9);
        std::cout << " sec " << std::endl;
    }

    BOOST_AUTO_TEST_CASE(case_output_read_integer)
    {
        Tuple tuple = Tuple({123});
        TuplePattern tuplePattern = TuplePattern("integer:*");
        auto start = std::chrono::high_resolution_clock::now();
        std::ios_base::sync_with_stdio(false);

        for( int i = 0; i< 5; ++i)
            linda_output(tuple);

        for( int i = 0; i< 1; ++i) {
            std::optional<Tuple> t = linda_read(tuplePattern, 1000);
            bool isMatch = tuplePattern.checkIfMatch(*t);
            BOOST_TEST(isMatch);
        }
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken =(double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        std::cout << "Time taken by program is : " << std::fixed
                  << time_taken << std::setprecision(9);
        std::cout << " sec " << std::endl;
    }

    BOOST_AUTO_TEST_CASE(case_output_input_float)
    {
        Tuple tuple = Tuple({1.23f});
        TuplePattern tuplePattern = TuplePattern("float:<2.0");
        auto start = std::chrono::high_resolution_clock::now();
        std::ios_base::sync_with_stdio(false);

        for( int i = 0; i< 1; ++i)
            linda_output(tuple);

        for( int i = 0; i< 1; ++i) {
            std::optional<Tuple> t = linda_input(tuplePattern, 1000);
            bool isMatch = tuplePattern.checkIfMatch(*t);
            BOOST_TEST(isMatch);
        }
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        std::cout << "Time taken by program is : " << std::fixed
                  << time_taken << std::setprecision(9);
        std::cout << " sec " << std::endl;
    }

    BOOST_AUTO_TEST_CASE(timeout)
    {
        TuplePattern tuplePattern = TuplePattern("float:<2.0; string:==lalalalalalalalaXDDDDDD; integer:<= 101010");
        std::optional<Tuple> t = linda_input(tuplePattern, 1000);
        bool isSuccess = t == std::nullopt;
        BOOST_TEST(isSuccess);
    }

BOOST_AUTO_TEST_SUITE_END();