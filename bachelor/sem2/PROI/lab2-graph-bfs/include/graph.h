#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include "vertex.h"

template <class DataType>
class Graph{
public:

    Graph<DataType>(): numberOfVertexes_(0){}
    ~Graph<DataType>(){}
    void addVertex(const DataType&);
    bool addEdge( int firstIndex, int secondIndex );
    bool removeEdge( int firstIndex, int secondIndex );
    DataType& operator[](int vertexIndex);
    DataType operator[](int vertexIndex) const;
    int getSize() const {return numberOfVertexes_;}
    bool getNeighbours( int vertexNumber, std::vector<int>& neightboursVector );

    bool areConnected( int firstIndex, int secondIndex);



private:
    std::vector<Vertex<DataType>> vertexes_;
    std::vector< std::vector<int> > adjacencyList_;
    int numberOfVertexes_;

    bool isEdge_(int firstIndex, int secondIndex);
    void removeEdgeFromVector_(int firstIndex, int secondIndex);
    bool BFS_( int startIndex, std::vector<int>& visitedIndexes );
    bool checkIndex_( int indexToCheck );
};

#include "graph.tcc"
#include "bfs.tcc"

#endif
