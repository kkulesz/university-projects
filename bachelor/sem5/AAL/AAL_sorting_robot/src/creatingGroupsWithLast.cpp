//
// Created by demongo on 04.01.2021.
//
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include "../include/creatingGroupsWithLast.h"
#include "../include/utilities.h"


int heuristicLossCGWL(const std::vector<int>& data){

	int prev = data[0];
	int curr = data[1];

	int counter=0;
	if( prev != curr ){
		counter++;
	}
	for(int i=2; i<data.size(); i++){
		prev = curr;
		curr = data[i];

		if( prev != curr ){
			counter++;
		}
	}

	return counter;
}


bool worthSearching(const std::vector<int>& data, int& attempts, int& prevLoss,
                    int& loss, bool& somethingWrong, std::vector<std::vector<int>>& buffer){


	prevLoss = loss;
	loss = heuristicLossCGWL(data);

	if( loss >= prevLoss ){
		attempts++;
		somethingWrong = true;
		buffer.push_back(data);
	} else if(somethingWrong){
		attempts++;
	}

	if(attempts > 10){
		somethingWrong = false;

		std::set<std::vector<int>> s(buffer.begin(), buffer.end());
		bool sameFound = (s.size() != buffer.size());

		if(sameFound){
			return false;
		}else{
			attempts = 0;
			somethingWrong=false;
		}

	}

	return true;
}

int howManyLastsInCurrent4(std::queue<int> current4, int last){

	int counter=0;
	for(int i=0; i<4; i++){
		if(current4.front() == last){
			counter++;
		}else{
			return counter;
		}
		current4.pop();
	}

	return counter;

}

bool searchForIndexes(const std::vector<int>& data, std::queue<int> current4,
		int last, std::map<int, std::vector<int>>& indexesForNumberOfLastOccurrences,
		bool searchFor4){
	size_t size = data.size();
	for(int i=1; i<size-3; ++i){
		current4.pop();
		current4.push(data[i+3]);
		bool searchingInLastGroup = true;

		for(int j=size-1; j>i+3; j--){
			if( data[i+3] != data[j] ){
				searchingInLastGroup = false;
				break;
			}
		}

		if( searchingInLastGroup ){
			if( i == 1 ){
				//all colors same
				return false;
			}
			//searching in last group
			break;
		}

		int number = howManyLastsInCurrent4(current4, last);
		if(number == 0) continue;
		indexesForNumberOfLastOccurrences.find(number)->second.push_back(i);
		if(number == 4 && !searchFor4){
			break;
		}
	}
	return true;
}


int searchBest4ToSwap(const std::vector<int>& data, int last){

	std::queue<int> current4;
	for(int i=0; i<4; i++){
		current4.push(data[i]);
	}

	std::map<int, std::vector<int>> indexesForNumberOfLastOccurrences;
	for(int i=0; i<5; i++){
		indexesForNumberOfLastOccurrences.emplace(i, std::vector<int>());
	}


	int number = howManyLastsInCurrent4(current4, last);
	indexesForNumberOfLastOccurrences.find(number)->second.push_back(0);

	if(!searchForIndexes(data, current4, last, indexesForNumberOfLastOccurrences, false))
		return -1;

	//choose best candidate
	if(!indexesForNumberOfLastOccurrences.find(4)->second.empty()){
		return indexesForNumberOfLastOccurrences.find(4)->second[0];
	}else if(!indexesForNumberOfLastOccurrences.find(3)->second.empty()){
		return indexesForNumberOfLastOccurrences.find(3)->second[0];
	}else if(!indexesForNumberOfLastOccurrences.find(2)->second.empty()){
		return indexesForNumberOfLastOccurrences.find(2)->second[0];
	}else if(!indexesForNumberOfLastOccurrences.find(1)->second.empty()){
		return indexesForNumberOfLastOccurrences.find(1)->second[0];
	}else{
		return -1;
	}

}

int search4ToSwap(const std::vector<int>& data, int last){

	std::queue<int> current4;
	for(int i=0; i<4; i++){
		current4.push(data[i]);
	}

	std::map<int, std::vector<int>> indexesForNumberOfLastOccurrences;
	for(int i=0; i<5; i++){
		indexesForNumberOfLastOccurrences.emplace(i, std::vector<int>());
	}

	int number = howManyLastsInCurrent4(current4, last);
	indexesForNumberOfLastOccurrences.find(number)->second.push_back(0);


	if(!searchForIndexes(data, current4, last, indexesForNumberOfLastOccurrences, true))
		return -1;


	if(!indexesForNumberOfLastOccurrences.find(4)->second.empty()){
		return indexesForNumberOfLastOccurrences.find(4)->second[0];
	}else {
		return -1;
	}

}

void swapAllColor(std::vector<int>& data, int& numberOfMoves, int color){
	while(true){
		int index = search4ToSwap(data, color);

		if(index == -1){
			// cant swap
			break;
		}

		move4chars(data, index, numberOfMoves);
	}
}

void putAll4ToOrder(std::vector<int>& data, int& numberOfMoves){

	swapAllColor(data, numberOfMoves,C);
	swapAllColor(data, numberOfMoves,M);
	swapAllColor(data, numberOfMoves,Y);
	swapAllColor(data, numberOfMoves,K);


}

int creatingGroupsWithLast(std::vector<int>& data, bool versionWithSortFinish){
    int attempts = 0;
    int prevLoss = INT32_MAX;
    int loss = INT32_MAX;
    bool somethingWrong = false;
    std::vector<std::vector<int>> buffer;

	int last = *(data.end()-1);

	int numberOfMoves = 0;
	while (!isSorted(data) && worthSearching(data, attempts, prevLoss, loss, somethingWrong, buffer)){
		last = *(data.end()-1);

		int index = searchBest4ToSwap(data, last);

		if(index == -1){
			// cant swap
			break;
		}

		move4chars(data, index,numberOfMoves);
	}

	// activate this if
	if(versionWithSortFinish)
		putAll4ToOrder(data, numberOfMoves);

	return numberOfMoves;
}