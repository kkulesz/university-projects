#ifndef _BUILDINGS_H_
#define _BUILDINGS_H_

#include "worker.h"
#include <string>

class Building{
public:
	//enum type{nothing, GOLDMINE, SAW} type;
	enum state{BUILD, NOT_BUILD, DAMAGED} state;

	Worker* freeLaborer();
	Worker* setLaborer(Worker*);
	int& getCountdown(){ return countdown; }
	void changeWorking(bool new_state){ is_working = new_state; }

	virtual int const getProduction() = 0;
	//virtual int const getLumberCost() = 0;
	//virtual int const getGoldCost() = 0;
	//virtual std::string getName() = 0;
	virtual int const getRepairTime() = 0;
	virtual int const getGoldRepair() = 0;
	virtual int const getLumberRepair() = 0;

protected:
	Worker* laborer;
	bool is_working;
	int countdown;
	virtual ~Building(){}

};

#endif
