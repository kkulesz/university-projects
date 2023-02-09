//
// Created by demongo on 06.01.2021.
//

#include "../include/fast4Create.h"
#include "../include/creatingGroupsWithLast.h"
#include "../include/utilities.h"
#include <set>
#include <queue>
#include <map>
#include <iostream>
#include <unordered_map>


int heuristicLossF4C(std::vector<int> data){

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

bool worthSearching(std::vector<int> data, int& attempts, int& prevLoss,
                    int& loss, bool& somethingWrong, std::vector<std::vector<int>>& buffer) {

	prevLoss = loss;
	loss = heuristicLossF4C(data);

	if( loss >= prevLoss ){
		attempts++;
		somethingWrong = true;
		buffer.push_back(data);
	} else if(somethingWrong){
		attempts++;
	}

	if(attempts > 20) {
		somethingWrong = false;

		std::set<std::vector<int>> s(buffer.begin(), buffer.end());
		bool sameFound = (s.size() != buffer.size());

		if (sameFound) {
			return false;
		} else {
			attempts = 0;
			somethingWrong = false;
			buffer.clear();
		}
	}


	return true;
}

std::pair<int,int> searchForSmallGroupRight(std::vector<int> current4){


	int color = current4[3];
	int counter = 1;
	for(int i=2; i>=0; i--){
		if(current4[i] != color){
			break;
		}
		counter++;
	}

	return std::make_pair(color, counter);;
}

std::pair<int,int> searchForSmallGroupLeft(std::vector<int> current4){

	int color = current4[0];
	int counter = 1;
	for(int i=1; i<4; i++){
		if(current4[i] != color){
			break;
		}
		counter++;
	}

	return std::make_pair(color, counter);;
}

void addIndexToVector(int index, std::pair<int,int> colorAndGroupSize,
					  IndexVector& vector,
		const std::vector<int>& groups){


	for(int i=index; i<index+4; i++){
		if( groups[i] != -1 ){
			// collision with group
			return;
		}
	}

	int color = colorAndGroupSize.first;
	int size = colorAndGroupSize.second;

	vector[color][size].push_back(index);

}

void initializeIndexesVector(IndexVector& vector){

	for(int i=0; i<4; i++){
		vector.push_back(std::vector<std::vector<int>>());
	}

	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			vector[i].push_back(std::vector<int>());
		}
	}

}

void searchForIndexes(const std::vector<int>& data,
					  IndexVector& indexVector, int skip, const std::vector<int>& groups,
					  std::vector<int> current4, bool right){
	size_t size = data.size();

	for(int i=1+skip; i<size-4; i++){

		int k = 0;
		for(int j=i; j<i+4; j++, k++){
			current4[k] = data[j];
		}

		std::pair<int,int> colorAndGroupSize;

		if(right)
			colorAndGroupSize = searchForSmallGroupRight(current4);
		else
			colorAndGroupSize = searchForSmallGroupLeft(current4);


		if(colorAndGroupSize.second != 4){
			addIndexToVector(i, colorAndGroupSize, indexVector, groups);
		}else{
			i+= 3;
		}
	}
}

int searchBest4ToMergeRight(const std::vector<int>& data, const std::vector<int>& groups){
	size_t size = data.size();

	std::vector<int> current4;
	for(int i=0; i<4; i++){
		current4.push_back(data[i]);
	}


	IndexVector indexesOfGroupRight;
	initializeIndexesVector(indexesOfGroupRight);



	std::pair<int,int> colorAndGroupSizeRight = searchForSmallGroupRight(current4);

	int skip = 0;
	if(colorAndGroupSizeRight.second != 4){
		addIndexToVector(0, colorAndGroupSizeRight, indexesOfGroupRight, groups);
	}else{
		skip = 3;
	}

	searchForIndexes(data, indexesOfGroupRight, skip, groups, current4, true);


	// return best
	for( int groupSize=3; groupSize>0; groupSize--){
		for(int color=0; color<4; color++){
			if( !indexesOfGroupRight[color][groupSize].empty() ){
				return indexesOfGroupRight[color][groupSize][0];
			}
		}
	}

	return -1;
}

int searchBest4ToMergeLeft(const std::vector<int>& data, const std::vector<int>& groups){
	size_t size = data.size();

	std::vector<int> current4;
	for(int i=0; i<4; i++){
		current4.push_back(data[i]);
	}


	IndexVector indexesOfGroupLeft;
	initializeIndexesVector(indexesOfGroupLeft);


	std::pair<int,int> colorAndGroupSizeLeft = searchForSmallGroupLeft(current4);


	int skip = 0;
	if(colorAndGroupSizeLeft.second != 4){
		addIndexToVector(0, colorAndGroupSizeLeft, indexesOfGroupLeft, groups);
	}else{
		skip = 3;
	}

	searchForIndexes(data, indexesOfGroupLeft, skip, groups, current4, false);


	int color = data[size-1];
	for( int groupSize=3; groupSize>0; groupSize--){
		if( !indexesOfGroupLeft[color][groupSize].empty() ){
			return indexesOfGroupLeft[color][groupSize][0];
		}
	}

	return -1;
}

bool checkIfIsAll4(std::vector<int> current4){

	int color = current4[0];
	for(int i=1; i<4; i++){
		if(current4[i] != color){
			return false;
		}
	}

	return true;
}

void setGroup(std::vector<int>& groups, int startIndex, int groupNumber){
	for(int i=startIndex; i<startIndex+4; i++){
		groups[i] = groupNumber;
	}
}

void makeGroups(const std::vector<int>& data, std::vector<int>& groups){

	size_t size = data.size();

	// clear the vector
	for(int i=0; i<size; i++){
		groups[i] = -1;
	}

	std::vector<int> current4;
	for(int i=0; i<4; i++){
		current4.push_back(data[i]);
	}

	bool oneColor = checkIfIsAll4(current4);
	int skip = 0;
	int groupNumber = 0;
	if( oneColor ){
		// has one colors
		setGroup(groups, 0, groupNumber);
		groupNumber++;
		skip = 3;
	}

	for(int i=1+skip; i<size-3; i++){

		int k = 0;
		for(int j=i; j<i+4; j++, k++){
			current4[k] = data[j];
		}

		oneColor = checkIfIsAll4(current4);
		if( oneColor ){
			// has one colors
			setGroup(groups, i, groupNumber);
			groupNumber++;
			i+= 3;
		}

	}

}


int findGroupInLast8(const std::vector<int>& data, const std::vector<int>& groups){
	size_t size = data.size();
	int counter = 0;

	int group = groups[size-8];
	for(int i=size-7; i<size; i++){
		if( groups[i] != -1 ) {
			return i;
		}
	}
	return -1;
}

void swapAllColor(std::vector<int>& data, std::vector<int>& groups, int& numberOfMoves, int color){
	while(true){
		int index = search4ToSwap(data, color);

		if(index == -1){
			// cant swap
			break;
		}

		move4chars(data, index, numberOfMoves);
		makeGroups(data, groups);
	}
}

void putAll4ToOrder(std::vector<int>& data, int& numberOfMoves, std::vector<int>& groups){

	swapAllColor(data, groups, numberOfMoves, C);
	swapAllColor(data, groups, numberOfMoves, M);
	swapAllColor(data, groups, numberOfMoves, Y);
	swapAllColor(data, groups, numberOfMoves, K);

}


bool rightSwap(std::vector<int>& data, std::vector<int>& groups, int& numberOfMoves){
	int index = searchBest4ToMergeRight(data, groups);

	if(index == -1){
		// try order
		putAll4ToOrder(data, numberOfMoves, groups);

		index = searchBest4ToMergeRight(data, groups);
		if( index == -1){
			// cant swap
			return false;
		}
	}

	move4chars(data, index, numberOfMoves);
    move4charsGroups(groups, index);

	makeGroups(data, groups);

	return true;
}

bool leftSwap(std::vector<int>& data, std::vector<int>& groups, int& numberOfMoves){
	int index = searchBest4ToMergeLeft(data, groups);

	if(index == -1){
		//	try order
		putAll4ToOrder(data, numberOfMoves, groups);

		index = searchBest4ToMergeLeft(data, groups);
		if( index == -1){
			// cant swap
			return false;
		}
	}

	move4chars(data, index, numberOfMoves);
    move4charsGroups(groups, index);


	makeGroups(data, groups);

	return true;
}


bool swapCreatedGroup(std::vector<int>& data, std::vector<int>& groups, int& numberOfMoves){
	int index = findGroupInLast8(data, groups);

	if(index == -1){
		// cant swap
		return false;
	}

	move4chars(data, index, numberOfMoves);
    move4charsGroups(groups, index);


	makeGroups(data, groups);

	return true;
}

int fast4Create(std::vector<int>& data, bool versionWithSortFinish){
	size_t size = data.size();

    int attempts = 0;
    int prevLoss = INT32_MAX;
    int loss = INT32_MAX;
    bool somethingWrong = false;
    std::vector<std::vector<int>> buffer;

	std::vector<int> groups;
	groups.resize(size);
	std::fill(groups.begin(), groups.end(), -1);

	makeGroups(data, groups);

	int numberOfMoves = 0;
	while (!isSorted(data) && worthSearching(data, attempts, prevLoss, loss, somethingWrong, buffer)){

		if(!rightSwap(data, groups, numberOfMoves))
			break;

		if(!leftSwap(data, groups, numberOfMoves))
			continue;

		if(!swapCreatedGroup(data, groups, numberOfMoves))
			continue;

	}

	// activate this if
	if(versionWithSortFinish)
		putAll4ToOrder(data, numberOfMoves, groups);

	return numberOfMoves;

}