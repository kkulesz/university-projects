#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "interface.h"


TEST_CASE( "adding player to game", "[game_start]" ){
	Logic logic;
	
	SECTION("adding player"){
		logic.startGame(1);
		REQUIRE( logic.isPlayerAvailable() );
		
		SECTION("removing player"){
			logic.endGame();
			REQUIRE( !logic.isPlayerAvailable() );
		}
	}//adding player
}

TEST_CASE( "adding materials to player", "[end_turn]" ){
	Player* player = new Player();
	int previousGold = player->getGold();
	int previousLumber = player->getLumber();
	BuildingManager bm;
	WorkerManager wm;
	wm.setPlayer(player);
	bm.setPlayer(player);
	bm.endTurn();
	int currentGold = player->getGold();
	int currentLumber = player->getLumber();
	Worker* worker = new Worker();

	SECTION("checking gold"){
		GoldMine tmp(worker,1);
		REQUIRE( currentGold - previousGold == tmp.getProduction());
	}
	SECTION("checking lumber"){
		Saw tmp(worker,1);
		REQUIRE( currentLumber - previousLumber == tmp.getProduction());
	}
	bm.clearMemory();
	wm.clearMemory();
	delete player;
	delete worker;
}
