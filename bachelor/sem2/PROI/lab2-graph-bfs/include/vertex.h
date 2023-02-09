#ifndef _VERTEX_H_
#define _VERTEX_H_

template <class DataType>
class Vertex{
public:
    Vertex(DataType newData, int initIndex): data_(newData), index_(initIndex){}
    DataType& getData(){ return data_; }
    DataType getConstData() const { return data_; }
    int getIndex() const { return index_; }
private:
    DataType data_;
    int index_;
};

#endif
