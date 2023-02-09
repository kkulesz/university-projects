#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
bool read( const std::string& fileName, std::vector<std::string>& data)
{
    std::fstream file;
    bool is_problem=false;
    file.open( fileName, std::ios::in );
    if( file.is_open() )
    {
        while( file.good() )
        {
            std::string tmp_string;
            file>>tmp_string;
            if(file)
                data.push_back(tmp_string);
        }
        if(!file)
            is_problem=true;
    }
    else
    {
        return false;
    }
    file.close();
    return is_problem;
}



template<typename IteratorType>
void bubbleSort(IteratorType first, IteratorType last){
    int sortedElements = 0;
    bool isSorted = false;
    for(IteratorType it = first; it!=last && isSorted != true; ++it){
	    isSorted = true;
        for(IteratorType it2 = first; it2!=last - 1 - sortedElements; ++it2){
            if( *it2>*(it2+1) ){
                std::swap(*it2,*(it2+1));
		isSorted = false;
	    }
        }
        ++sortedElements;
    }
}

template<typename IteratorType>
std::vector<typename IteratorType::value_type> merge(IteratorType first, IteratorType last, IteratorType pivot){

    std::vector<typename IteratorType::value_type> collection;

    IteratorType left_begin{first} , left_end{pivot},
		 right_begin{pivot}, right_end{last};


    while( left_begin != right_begin && left_end != right_end ){
/*
   	 if( *left_begin <= *left_end ){
	  	collection.push_back(*left_begin);
	  	++left_begin;
	 }else{
	 	collection.push_back(*left_end);
	 	++left_end;
	 }
*/	  

    collection.push_back((*left_begin <= *left_end) ? *left_begin++ : *left_end++);
    }

    collection.insert(collection.end(), left_begin, right_begin);
    collection.insert(collection.end(), left_end, right_end);
//thanks to it we do not have to clear collection
    return std::move(collection);
}

template<typename IteratorType>
void mergeSort(IteratorType first, IteratorType last){

    if(first < last){
        int pivot = std::distance(first, last);
        if(pivot<2){
            return;
        }
        pivot/=2;

        mergeSort<IteratorType>(first, first+pivot);
        mergeSort<IteratorType>(first+pivot, last);

        auto vec = merge(first,last, first+pivot);
	//moves elements if range of vec.cbegin() to vec.cend() after first
        std::move(vec.cbegin(), vec.cend(), first);
    }

}


int main( int argc, char** argv){
    std::vector<std::string> stringVector;
    read(argv[1], stringVector);

    std::vector<std::string> forBubble{stringVector}, forMerge{stringVector};

    int wordNumber=1000;

    std::cout<<"============stl::sort============"<<std::endl;
    auto beforeSort = std::chrono::high_resolution_clock::now();
    std::sort<std::vector<std::string>::iterator>(stringVector.begin(),stringVector.begin()+ wordNumber);
    auto afterSort = std::chrono::high_resolution_clock::now();
    for(int i=0; i<wordNumber;++i){
        std::cout<<stringVector[i]<<std::endl;
    }


    std::cout<<"============bubble============"<<std::endl;
    auto beforeBubbleSort = std::chrono::high_resolution_clock::now();  
    bubbleSort<std::vector<std::string>::iterator>(forBubble.begin(),forBubble.begin()+ wordNumber);
    auto afterBubbleSort = std::chrono::high_resolution_clock::now();

    for(int i=0; i<wordNumber;++i){
        std::cout<<forBubble[i]<<std::endl;
    }
   

    std::cout<<"============Merge============"<<std::endl;
    auto beforeMergeSort = std::chrono::high_resolution_clock::now(); 
    mergeSort<std::vector<std::string>::iterator>(stringVector.begin(),stringVector.begin()+ wordNumber);
    auto afterMergeSort = std::chrono::high_resolution_clock::now(); 
    for(int i=0; i<wordNumber;++i){
        std::cout<<stringVector[i]<<std::endl;
    }


    auto sortTime = std::chrono::duration_cast<std::chrono::microseconds>(afterSort-beforeSort);
    auto bubbleTime = std::chrono::duration_cast<std::chrono::microseconds>(afterBubbleSort-beforeBubbleSort);
    auto mergeTime = std::chrono::duration_cast<std::chrono::microseconds>(afterMergeSort-beforeMergeSort);
    
 

    std::cout<<"============Comparison============"<<std::endl;
    std::cout<<"Time for "<<wordNumber<<" elements"<<std::endl
	    <<"bubblesort:"<<bubbleTime.count()<<std::endl
	    <<"mergesort: "<<mergeTime.count()<<std::endl
	    <<"std::sort: "<<sortTime.count()<<std::endl;
    return 0;
}
