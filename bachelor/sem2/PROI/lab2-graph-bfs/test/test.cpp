#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "graph.h"


TEST_CASE( "graph", "[graph], [functions]" ){
    Graph<int> int_graph;
    SECTION("checking if size after initialization is equal 0"){
        REQUIRE( int_graph.getSize() == 0);
    }

    int data[4] = {58,24,-75,31};
    int_graph.addVertex( data[0] );
    int_graph.addVertex( data[1] );
    int_graph.addVertex( data[2] );
    int_graph.addVertex( data[3] );

    SECTION("checking if size gets updated"){
        REQUIRE( int_graph.getSize() == sizeof(data)/sizeof(data[0]) );
    }

    SECTION("getting data from graph using operator[]"){
        REQUIRE( int_graph[0] == data[0] );
    }

    SECTION("changing data using operator[]"){
        int_graph[0] += 1;
        REQUIRE( int_graph[0] == data[0]+1 );
    }

    SECTION("areConnected() and BFS()"){
        SECTION("adding and removing edge"){
            int_graph.addEdge(0,1);
            REQUIRE( int_graph.areConnected(0,1) );
            int_graph.removeEdge(0,1);
            REQUIRE( !int_graph.areConnected(0,1) );
        }
        int_graph.addEdge(0,1);
        int_graph.addEdge(1,2);
        int_graph.addEdge(2,3);
        REQUIRE( int_graph.areConnected(0,3) );

        int_graph.removeEdge(1,2);
        REQUIRE( !int_graph.areConnected(0,3) );
        int_graph.removeEdge(0,1);
        int_graph.removeEdge(2,3);
    }

    SECTION("adding edge between non-existing vertexes "){
        REQUIRE( !int_graph.addEdge( 100,101 ) );
    }
    SECTION("removing edge between non-existing vertexes "){
        REQUIRE( !int_graph.removeEdge(100,101) );
    }

    SECTION("getNeighbours()"){
        int_graph.addEdge(0,1);
        int_graph.addEdge(0,2);
        int_graph.addEdge(0,3);
        std::vector<int> neighbours;
        REQUIRE( int_graph.getNeighbours(0,neighbours) );
        REQUIRE( !int_graph.getNeighbours(100, neighbours) );
        REQUIRE( neighbours[0] == 1 );
        REQUIRE( neighbours[1] == 2 );
        REQUIRE( neighbours[2] == 3 );
    }
}
