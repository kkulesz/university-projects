//
// Created by demongo on 03.01.2021.
//


#include "../include/utilities.h"

#include <cstring>
#include <iostream>
#include <cstdlib>
#include <queue> //fifo
#include <algorithm>
#include <sstream>

extern bool DEBUG;




void swapAndAppend(std::vector<int>& data, int& degraded, int& upgraded){
	std::swap(degraded, upgraded);
	data.push_back(degraded);
}

void generateData(std::vector<int>& data, size_t size, const int chance_of_duplication){
	if( chance_of_duplication < 0 || chance_of_duplication > 100 || size<=0){
		throw;
	}
	int chance_of_change = (100 - chance_of_duplication)/3;

	int privileged;
	int rest[3];

	int random = rand()%100;
	if(random <= 25){//choose first privileged and set the rest
		privileged = C;
		rest[0] = M; rest[1] = Y; rest[2] = K;
	}else if(random <= 50){
		privileged = M;
		rest[0] = C; rest[1] = Y; rest[2] = K;
	}else if(random <= 75){
		privileged = Y;
		rest[0] = C; rest[1] = M; rest[2] = K;
	}else{
		privileged = K;
		rest[0] = C; rest[1] = M; rest[2] = Y;
	}
	data.push_back(privileged);

	while(--size){
		random = rand()%100;
		if(random < chance_of_duplication){
			data.push_back(privileged);
		}else if(random < chance_of_duplication + chance_of_change){
			swapAndAppend(data, privileged, rest[0]);
		}else if( random < chance_of_duplication + chance_of_change*2){
			swapAndAppend(data, privileged, rest[1]);
		}else{
			swapAndAppend(data, privileged, rest[2]);
		}
	}
}

void move4chars(std::vector<int>& data, const int index, int& numberOfMoves){
	int size = data.size();
	if(index < 0 || index > size-4){
	    std::cout<<"move4chars throw- index: "<<index<<std::endl;
		throw;
	}

	std::vector<int> mid;
	std::vector<int> end;

	mid.resize(size);
	end.resize(size);

	int beg_len = index;
	int mid_len = 4;
	int end_len = size - index-4;

	//copy mid and end
	std::copy_n(data.begin() + index, mid_len, mid.begin());
	std::copy_n(data.begin() + index + mid_len, end_len, end.begin());

	if(DEBUG == true){
        std::cout<<vToStrDebug(data, index)<<"\n";
        std::cin.get();
	}

	//copy in different_order
	std::copy_n(end.begin(), end_len, data.begin() + beg_len);
	std::copy_n(mid.begin(), mid_len, data.begin() + beg_len + end_len);

    ++numberOfMoves;
}

void move4charsGroups(std::vector<int>& data, const int index){
    int size = data.size();
    if(index < 0 || index > size-4){
        std::cout<<"move4chars throw- index: "<<index<<std::endl;
        throw;
    }

    std::vector<int> mid;
    std::vector<int> end;

    mid.resize(size);
    end.resize(size);

    int beg_len = index;
    int mid_len = 4;
    int end_len = size - index-4;

    //copy mid and end
    std::copy_n(data.begin() + index, mid_len, mid.begin());
    std::copy_n(data.begin() + index + mid_len, end_len, end.begin());

    //copy in different_order
    std::copy_n(end.begin(), end_len, data.begin() + beg_len);
    std::copy_n(mid.begin(), mid_len, data.begin() + beg_len + end_len);
}

bool isSorted(std::vector<int> data){
	size_t size = data.size();
	if(size <= 0){
	    std::cout<<"isSorted throw"<<std::endl;
		throw;
	}

	std::vector<int> buff = data;
	std::sort(buff.begin(), buff.end());

	for(int i=0; i<size; i++){
		if( buff[i] != data[i] )
			return false;
	}
	return true;
}

std::string vToStr(std::vector<int> data){
	std::stringstream ss;
	for(auto x: data){
		switch(x){
			case C:
				ss << 'C';
				break;
			case M:
				ss << 'M';
				break;
			case Y:
				ss << 'Y';
				break;
			case K:
				ss << 'K';
				break;
			default:
                std::cout<<"vToStr() throw"<<std::endl;
				throw;
		}
	}
	return ss.str();
}

std::string vToStrDebug(std::vector<int> data, int index){
    std::stringstream ss;
    for(int i=0; i<data.size(); ++i){
        if(i == index || i == index+4){
            ss << '*';
        }
        switch(data[i]){
            case C:
                ss << 'C';
                break;
            case M:
                ss << 'M';
                break;
            case Y:
                ss << 'Y';
                break;
            case K:
                ss << 'K';
                break;
            default:
                std::cout<<"vToStrDebug() throw"<<std::endl;
                throw;
        }
    }
    return ss.str();
}

int heuristicLoss(std::vector<int> data){
	size_t size = data.size();
	if( size <= 0 ){
        std::cout<<"heuristicLoss() throw"<<std::endl;
		throw;
	}
	int loss=0;
	std::vector<int> tmp;
	tmp = data;
	std::sort(tmp.begin(), tmp.end());
	for (int i = 0; i < size; ++i) {
		if( tmp[i] != data[i]){
			++loss;
		}
	}
	return loss;
}

std::vector<int> convertToData(const char* arr, int size){
    std::vector<int> data;
    for(int i=0; i<size; ++i){
        if(arr[i] == 'C'){
            data.push_back(C);
        }else if(arr[i] == 'M'){
            data.push_back(M);
        }else if(arr[i] == 'Y'){
            data.push_back(Y);
        }else if(arr[i] == 'K'){
            data.push_back(K);
        }else{
            std::cout<<"convertToData throw"<<std::endl;
            throw;
        }
    }
    return std::move(data);
}
