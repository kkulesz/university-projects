//
// Created by demongo on 03.01.2021.
//

#include "../include/bruteForce.h"

#include <cstring>
#include <queue> //fifo
#include <cmath>

int bruteForce(std::vector<int>& data, int& bestNumOfMoves){
	size_t size = data.size();

	int numberOfMoves = 0;

	if(size <=4){
		throw;
	}

	std::queue<std::vector<int>> fifo;
	const size_t num_of_children = size-5;
	fifo.push(data);

	int iterations = 0;
	std::vector<int> tmp;
	while(true){
		tmp = fifo.front();
		fifo.pop();

		if(isSorted(tmp)){
			data = tmp;
			while(!fifo.empty()){
				fifo.pop();
			}
            bestNumOfMoves = (int)ceil(log(iterations)/log(num_of_children));
			return iterations;
		}

		for(int i=0; i<num_of_children; ++i) {
			std::vector<int> child;
			child = tmp;
			move4chars(child, i,numberOfMoves);
			fifo.push(child);
		}
		++iterations;
	}


}