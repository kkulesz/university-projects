#include <iostream>
#include "logic.h"

void Logic::startGame( int num_of_players){
	if( num_of_players <= 0){
		return;
	}
	this->current_player_index = 0;
	for( int i = 0; i<num_of_players; i++ ){
		Player* new_player = new Player();
		this->players.push_back( new_player );	
	}
	
	BuildingManager* building_manager = new BuildingManager();
	WorkerManager* worker_manager = new WorkerManager();
	this->building_manager = building_manager;
	this->worker_manager = worker_manager;
	
	this->current_player = this->players[0];
	this->worker_manager->setPlayer(current_player);
	this->setPlayerToManagers(current_player);
}

void Logic::endTurnActions(){
	this->worker_manager->endTurn();
	this->building_manager->endTurn();
}

void Logic::switchPlayer(  ){
	++(this->current_player_index);
	this->current_player_index %= this->players.size();
	this->current_player = this->players[current_player_index];
	this->worker_manager->setPlayer(current_player);
	this->setPlayerToManagers(current_player);
}

void Logic::startTurnActions( std::string& message ){
	this->worker_manager->startTurn(message);
	this->building_manager->startTurn(message);

}

void Logic::train( std::string& message ){
	this->worker_manager->train( message );
}

void Logic::buildGoldMine( std::string& message){
	this->building_manager->buildGoldMine( message );
}

void Logic::buildSaw(std::string& message){
	this->building_manager->buildSaw( message );
}

void Logic::repairGoldMine( std::string& message ){
	this->building_manager->repair(BuildingManager::GOLDMINE, message);
}
void Logic::repairSaw( std::string& message ){
	this->building_manager->repair(BuildingManager::SAW, message);
}

void Logic::endGame(){
	for( int i = players.size()-1; i >= 0; --i ){
		this->setPlayerToManagers(players[i]);
		this->building_manager->clearMemory();
		this->worker_manager->clearMemory();
		Player* tmp = players[i];
		this->players.erase( players.begin() + i);
		delete tmp;
	}
	delete building_manager;
	delete worker_manager;
}


void Logic::getState(std::string& message){
	this->building_manager->getMaterials(message);
	this->worker_manager->getWorkers(message);
	this->building_manager->getBuildings(message);
}

bool Logic::isPlayerAvailable(){
	return (this->players.size() > 0);
}

void Logic::setPlayerToManagers(Player* new_player){
	this->worker_manager->setPlayer(new_player);
	this->building_manager->setPlayer(new_player);
}

