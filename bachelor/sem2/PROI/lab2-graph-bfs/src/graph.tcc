template <class DataType>
void Graph<DataType>::addVertex(const DataType& newElement ){
    Vertex<DataType> newVertex(newElement, this->numberOfVertexes_);
    this->vertexes_.push_back(newVertex);
    ++(this->numberOfVertexes_);

    std::vector<int> newAdjacencyList;
    this->adjacencyList_.push_back( newAdjacencyList );
}

template <class DataType>
bool Graph<DataType>::addEdge( int firstIndex, int secondIndex ){
    if( !checkIndex_(firstIndex) || !checkIndex_(secondIndex) || firstIndex==secondIndex ){
        return false;
    }
    if( this->isEdge_(firstIndex, secondIndex) ){
        return true;
    }else{
        this->adjacencyList_[firstIndex].push_back(secondIndex);
        this->adjacencyList_[secondIndex].push_back(firstIndex);
    }

    return true;
}

template <class DataType>
bool Graph<DataType>::removeEdge( int firstIndex, int secondIndex ){
    if( !checkIndex_(firstIndex) || !checkIndex_(secondIndex) ){
        return false;
    }
    if( !this->isEdge_(firstIndex, secondIndex) ){
        return true;
    }else{
        this->removeEdgeFromVector_(firstIndex, secondIndex);
        this->removeEdgeFromVector_(secondIndex, firstIndex);
    }
    return true;
}

template <class DataType>
DataType& Graph<DataType>::operator[]( int vertexIndex ){
    return this->vertexes_[vertexIndex].getData();
}

template <class DataType>
DataType Graph<DataType>::operator[]( int vertexIndex ) const{
    return this->vertexes_[vertexIndex].getConstData();
}

template <class DataType>
bool Graph<DataType>::getNeighbours( int vertexIndex, std::vector<int>& neighbourVector ){
    if( !checkIndex_(vertexIndex) ){
        return false;
    }
    neighbourVector = adjacencyList_[vertexIndex];
    return true;
}

template <class DataType>
bool Graph<DataType>::isEdge_(int firstIndex, int secondIndex){
    int size = this->adjacencyList_[firstIndex].size();
    for( int i = 0; i<size; ++i ){
        if( this->adjacencyList_[firstIndex][i] == secondIndex ){
            return true;
        }
    }
    return false;
}

template <class DataType>
void Graph<DataType>::removeEdgeFromVector_(int firstIndex, int secondIndex){
    int size = this->adjacencyList_[firstIndex].size();
    for( int i=0; i<size; ++i){
        if( this->adjacencyList_[firstIndex][i] == secondIndex ){
            this->adjacencyList_[firstIndex].erase( this->adjacencyList_[firstIndex].begin() + i);
            break;
        }
    }
}

template <class DataType>
bool Graph<DataType>::checkIndex_( int indexToCheck ){
    if( indexToCheck >= this->numberOfVertexes_ || indexToCheck < 0){
        return false;
    }else{
        return true;
    }
}
