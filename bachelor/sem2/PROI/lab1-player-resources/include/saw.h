#ifndef _SAW_H_
#define _SAW_H_

#include "buildings.h"

class Saw: public Building{
public:
	Saw(Worker*);
	Saw(Worker*, int i);//special constructor to get it ready immidiatly(for game start)
	static int const getLumberCost(){ return LUMBER_COST; }
	static int const getGoldCost() { return GOLD_COST; }
	int const getProduction();
	static std::string getName(){ return "Tartak";}
	int const getRepairTime(){ return REPAIR_TIME; }
	int const getGoldRepair() { return GOLD_REPAIR; }
	int const getLumberRepair() { return LUMBER_REPAIR; }
private:
	static const int LUMBER_PRODUCTION = 20;

	static const int GOLD_COST = 80;
	static const int LUMBER_COST = 70;
	static const int BUILD_TIME = 2;

	static const int REPAIR_TIME = 1;
	static const int GOLD_REPAIR = 20;
	static const int LUMBER_REPAIR = 40;
};

#endif
