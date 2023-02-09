//
// Created by demongo on 03.01.2021.
//

#ifndef PROJEKT_UTILITIES_H
#define PROJEKT_UTILITIES_H


#include <vector>
#include <string>

typedef enum Color{C, M, Y, K} Color;


const int DATA_SIZE =500;
const int CHANCE_OF_DUPLICATION = 10;


void swapAndAppend(std::vector<int>& data, int& degraded, int& upgraded);
void generateData(std::vector<int>& data, size_t size, const int chance_of_duplication);
void move4chars(std::vector<int>& data, const int index, int& numberOfMoves);
void move4charsGroups(std::vector<int>& data, const int index);
bool isSorted(std::vector<int> data);
std::string vToStr(std::vector<int> data);
std::string vToStrDebug(std::vector<int> data, int index);
int heuristicLoss(std::vector<int> data);
std::vector<int> convertToData(const char* arr, int size);

#endif //PROJEKT_UTILITIES_H
