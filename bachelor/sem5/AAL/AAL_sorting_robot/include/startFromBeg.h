//
// Created by Konrad Kulesza on 1/4/2021.
//

#ifndef PROJEKT_STARTFROMBEG_H
#define PROJEKT_STARTFROMBEG_H

#include <vector>

int startFromBeg(std::vector<int>& data);
int getNext(std::vector<int>& data, int howManySorted);
int getHowManySorted(std::vector<int>& data, int howManySorted);
int find4thPlus1(std::vector<int>& data, int howManySorted, int next);
int findPositionOfNext(std::vector<int>& data,int howManySorted,int next);
int manipulateEnd(std::vector<int>& data,int howManySorted, int indexOfNext, int& numberOfMoves);
int manipulateUntil4thPlus1(std::vector<int>& data, int howManySorted, int next, int& numberOfMoves);

#endif //PROJEKT_STARTFROMBEG_H
