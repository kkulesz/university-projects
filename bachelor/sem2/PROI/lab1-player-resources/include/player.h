#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>

#include "buildings.h"
#include "saw.h"
#include "goldmine.h"

class Player{
public:
	Player();
	void addGold(int const);
	void addLumber(int const);

	
	std::vector<Worker*> workers;
	std::vector<GoldMine*> goldmines;
	std::vector<Saw*> saws;
	//getters
	int const getGold(){ return gold; }
	int const getLumber() { return lumber; }
	
private:
	int gold;
	int lumber;

};



#endif 
