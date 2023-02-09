#ifndef _WORKER_MANAGER_H
#define _WORKER_MANAGER_H_

#include <string>
#include "managers.h"

class WorkerManager: public Manager{
public:
	void clearMemory();
	void train( std::string& );
	void getWorkers(std::string& );
	void endTurn();
	void startTurn( std::string& );
	
private:
	bool continueTraining( Worker*, int& finished_workers );
};

#endif
