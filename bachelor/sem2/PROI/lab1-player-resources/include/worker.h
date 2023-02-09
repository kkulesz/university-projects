#ifndef _WORKER_H_
#define _WORKER_H_

#include <string>

class Worker{
public:
	enum state{ FREE, TRAINING, BUSY } state;
	Worker();
	Worker(int);//special constructor to get it ready immidiatly(for game start)
	static int const getGoldCost() { return GOLD_COST; }
	static int const getLumberCost() { return LUMBER_COST; }
	/* decrement worker's countdown if it is >0
	changing worker status to TRAIN if countdown reaches 0 during function */
	void continueTraining();
	int& getCountdown(){ return countdown; }
	static std::string const getName(){ return "Pracownik"; }
private:
	static const int TRAIN_TIME = 1;
	static const int GOLD_COST = 30;
	static const int LUMBER_COST = 0;
	int countdown;
};

#endif
