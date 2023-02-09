//
// Created by demongo on 04.01.2021.
//

#ifndef PROJEKT_CREATINGGROUPSWITHLAST_H
#define PROJEKT_CREATINGGROUPSWITHLAST_H

#include <vector>

int creatingGroupsWithLast(std::vector<int>& data, bool versionWithSortFinish);
//bool worthSearching(const std::vector<int>& data);
//void putAll4ToOrder(std::vector<int>& data, int& numberOfMoves);
//int searchBest4ToSwap(std::vector<int> data, int last);
int search4ToSwap(const std::vector<int>& data, int last);

#endif //PROJEKT_CREATINGGROUPSWITHLAST_H
