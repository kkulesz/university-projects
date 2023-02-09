#ifndef _MANAGERS_H_
#define _MANAGERS_H_

#include "player.h"
//#include <functional>
#include <iostream>


class Manager{
public:
	virtual void endTurn() = 0;
	//virtual void startTurn() = 0;
	virtual void clearMemory() = 0;
	void const getMaterials(std::string& messege);
	Player* getPlayer() { return current_player; };
	void setPlayer(Player* new_player){ current_player = new_player; };
	virtual ~Manager(){}
protected:
	/* substracts given materials from player's ones */
	void subtractCost( int gold, int lumber);

	/* returns true if player's materials are higher than given ints */
	bool checkCost( int gold, int lumber );
	Player* current_player;
};

#endif



//void subtractCost( Player&, T&, std::function<int()>getGold, std::function<int()>getLumber );
	//bool checkCost( Player&, T&, std::function<int()>getGold, std::function<int()>getLumber );
	//T tmp = vec[i];//zeby to nizej działało
	//this->subtractCost( player, tmp, [tmp]()->int{ return tmp->getGoldRepair();}, [tmp]()->int{ return tmp->getLumberRepair();} );
