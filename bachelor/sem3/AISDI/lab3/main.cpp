#include <iostream>
#include <fstream>
#include <vector>

#include "heap.h"
#include "benchmark.h"



void read( const std::string& fileName, std::vector<std::string>& data)
{
    std::fstream file;
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
    }
    file.close();
}


int main(int argc, char** argv){

    return 0;
}