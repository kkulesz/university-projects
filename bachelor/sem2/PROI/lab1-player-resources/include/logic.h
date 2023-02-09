#ifndef _LOGIC_H_
#define _LOGIC_H_

#include <vector>
#include "player.h"
#include "building_manager.h"
#include "worker_manager.h"

class Logic{
public:
	/* adds number of players given by user */
	void startGame( int num_of_players );

	/* clears allocated memory at the end of the game */
	void endGame();

	/* class endTunr() for each manager*/
	void endTurnActions();
	
	void switchPlayer();

	/* calls startTurn() for each manager */
	void startTurnActions( std::string& );

	void train( std::string& );
	void buildGoldMine( std::string& );
	void buildSaw(std::string& );
	void repairGoldMine( std::string& );
	void repairSaw( std::string& );
	void getState(std::string& );
	

	Player* getPlayer(){ return current_player; }
	bool isPlayerAvailable();
	int getPlayerNumber(){ return current_player_index+1; }
private:
	int current_player_index;
	std::vector<Player*> players;
	Player* current_player;
	BuildingManager* building_manager;
	WorkerManager* worker_manager;
	void setPlayerToManagers(Player*);
};

#endif
