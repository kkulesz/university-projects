#include <iostream>
#include <ctime>
#include <cstdlib>

#include "managers.h"

void const Manager::getMaterials(std::string& message){
	message = "---Surowce---\nZloto: " + std::to_string(this->current_player->getGold()) + 
				"\tDrewno: " + std::to_string(this->current_player->getLumber());
}

void Manager::subtractCost( int goldCost, int lumberCost ){
	this->current_player->addGold( -goldCost );
	this->current_player->addLumber( -lumberCost );
}

bool Manager::checkCost( int goldCost, int lumberCost ){
	if( this->current_player->getGold() < goldCost ){
		return false;
	}
	if( this->current_player->getLumber() < lumberCost ){
		return false;
	}
	return true;
}

