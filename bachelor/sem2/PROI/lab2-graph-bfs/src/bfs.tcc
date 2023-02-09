template <class DataType>
bool Graph<DataType>::BFS_( int startIndex, std::vector<int>& visitedIndexes){
    if( !checkIndex_(startIndex) ){
        return false;
    }
    bool visited[numberOfVertexes_];
    for( int i = 0; i<numberOfVertexes_; ++i ){
        visited[i] = false;
    }
    visited[startIndex] = true;

    visitedIndexes.push_back(startIndex);

    std::vector<int> BFS_queue;
    BFS_queue.push_back(startIndex);

    while( BFS_queue.size() > 0 ){
        int current_index = BFS_queue[0];
        int number_of_neighbours = adjacencyList_[ current_index ].size();
        for(int i = 0; i< number_of_neighbours; ++i){
            if( visited[ adjacencyList_[current_index][i] ] == false  ){
                BFS_queue.push_back( adjacencyList_[current_index][i] );
                visitedIndexes.push_back( adjacencyList_[current_index][i] );
                visited[ adjacencyList_[current_index][i] ] = true;
            }
        }
        BFS_queue.erase( BFS_queue.begin() );
    }
    return true;
}


template <class DataType>
bool Graph<DataType>::areConnected( int firstIndex, int secondIndex ){
    if( !checkIndex_(firstIndex) || !checkIndex_(secondIndex) ){
        return false;
    }
    std::vector<int> connectedVertexesIndexes;
    this->BFS_(firstIndex, connectedVertexesIndexes);
    int length = connectedVertexesIndexes.size();
    for( int i = 0; i<length; ++i){
        if( secondIndex == connectedVertexesIndexes[i]){
            return true;
        }
    }
    return false;
}
