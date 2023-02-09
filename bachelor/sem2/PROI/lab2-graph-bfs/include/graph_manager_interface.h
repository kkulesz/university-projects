#ifndef _GRAPH_MANAGER_INTERFACE_H_
#define _GRAPH_MANAGER_INTERFACE_H_

#include "string"
#include "graph.h"

class Interface{
public:
    void printOptions();

    template <class DataType>
    void manageGraph( Graph<DataType>& );

private:
    int userInputInt_();
    std::string userInputString_();
    void userIndexesInput_(int& firstIndex, int& secondIndex);

    template<class DataType>
    void printVertexes_( const Graph<DataType> );
    template<class DataType>
    void readVertexesFromFile_( Graph<DataType>& );
    template<class DataType>
    void printNeighbours_( Graph<DataType> );

    static const int LEAVE_ = 0;
    static const int ADD_VERTEX_= 1;
    static const int ADD_EDGE_ = 2;
    static const int PRINT_VERTEXES_ = 3;
    static const int ARE_CONNECTED_ = 4;
    static const int REMOVE_EDGE_ = 5;
    static const int READ_FROM_FILE_ = 6;
    static const int GET_NEIGHBOURS_ = 7;

};

#include "graph_manager_interface.tcc"

#endif
