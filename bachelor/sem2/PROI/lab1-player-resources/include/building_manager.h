#ifndef _BUILDINGS_MANAGER_H_
#define _BUILDINGS_MANAGER_H_

#include "managers.h"

class BuildingManager: public Manager {
public:

	enum type{GOLDMINE = 1, SAW};

	void endTurn();
	void startTurn(std::string& message);
	void damage( Building* );
	/* Repairs goldmine or saw depending on given int */
	void repair( int option, std::string& message );

	void getBuildings( std::string& );
	void clearMemory( );

	/* Builds goldmine, if players state is valid. Changes message*/
	void buildGoldMine( std::string& message );

	/* Builds saw, if players state is valid. Changes message*/
	void buildSaw( std::string& message );

private:
	/* calls functions related to materials at the end of the turn */
	void endTurnMaterials();

	/* goes through vector and adds materials to player if certain building is working */
	template <class T>
	int collectMaterials( std::vector<T>& );
	
	/* calls function related to building, changes message */
	void startTurnBuilding( std::string& message );

	/* goes through vector and calls continueBuilding() for each element.
	 Increments counter if building is finished */
	template <class T>
	void manageBuilding( std::vector<T>&, int& counter);

	/* decrement builging's countdown if it's >0
	changing building state to BUILD if countdown reaches 0 during function */
	bool continueBuilding( Building*, int& counter );

	/* decrement builging's countdown if it's >0
	changing building state to BUILD if countdown reaches 0 during function */
	template <class T>
	void continueRepair( std::vector<T>&, Worker*, std::string& message );
	
	/* returns true if player have at least one free worker. changes index to the value of free worker's index
	sets message if doenst */
	bool checkWorker( int& index, std::string& message );


	/* substract player's materials if its state is valid */
	template <class T>
	bool checkBuild( T );

	template <class T>
	void freeVector(std::vector<T>&);

	void damageRandomly( std::string & message );

	template <class T>
	void countBuildings(std::vector<T> buildings, int& working, int& building, int& damaged);

	void getStatus( std::string, int& working, int& building, int& damaged, std::string& );

};

#endif

