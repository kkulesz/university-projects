#include "building_manager.h"
#include <string>
//////////////////////////BUILDING



void BuildingManager::endTurn(){
	this->endTurnMaterials();
}
void BuildingManager::startTurn(std::string& message){
	this->damageRandomly( message );
	this->startTurnBuilding( message );
}

void BuildingManager::damage( Building* building ){
	building->changeWorking(false);
	building->state = Building::state::DAMAGED;
	building->freeLaborer();
}


void BuildingManager::repair( int option, std::string& message ){
	int free_worker_index;
	if( this->checkWorker( free_worker_index, message ) ){
		if( option == BuildingManager::GOLDMINE){
			this->continueRepair( this->current_player->goldmines, this->current_player->workers[free_worker_index], message );
		}else if( option == BuildingManager::SAW){
			this->continueRepair( this->current_player->saws, this->current_player->workers[free_worker_index], message );
		}else{
			message = "BŁAD";
		}
	}
}

void BuildingManager::getBuildings( std::string& message){
	int working_gm = 0, building_gm = 0, damaged_gm = 0;
	int working_saw = 0, building_saw = 0, damaged_saw = 0;
	countBuildings(this->current_player->goldmines, working_gm, building_gm, damaged_gm );
	countBuildings(this->current_player->saws, working_saw, building_saw, damaged_saw );
	getStatus( "Kopalnie złota", working_gm, building_gm, damaged_gm, message );
	getStatus( "Tartaki", working_saw, building_saw, damaged_saw, message );
}

void BuildingManager::clearMemory(){
	this->freeVector(this->current_player->goldmines);
	this->freeVector(this->current_player->saws);
}

void BuildingManager::endTurnMaterials(){
	this->current_player->addGold( this->collectMaterials( this->current_player->goldmines ) );
	this->current_player->addLumber( this->collectMaterials( this->current_player->saws ) );
}


template <class T>
int BuildingManager::collectMaterials( std::vector<T>& vec){
	int new_materials = 0;
	for( int i=vec.size()-1; i>=0; --i ){
		new_materials += vec[i]->getProduction();
	}
	return new_materials;
}

void BuildingManager::startTurnBuilding( std::string& message ){
	int built_goldmines=0;
	int built_saws=0;
	this->manageBuilding( this->current_player->goldmines, built_goldmines );
	this->manageBuilding( this->current_player->saws, built_saws );
	if( built_goldmines > 0 ){
		message += "\nZakończono: kopalnia złota - " + std::to_string(built_goldmines);
	}
	if( built_saws > 0 ){
		message += "\nZakonczono: tartak - " + std::to_string(built_saws);
	}
}

template <class T>
void BuildingManager::manageBuilding( std::vector<T>& vec, int& counter){
	for( int i = vec.size()-1; i>=0; --i){
		this->continueBuilding(vec[i], counter);
	}
}


bool BuildingManager::continueBuilding( Building* building, int& counter ){
	if( building->state == Building::state::BUILD || building->getCountdown() == 0 ){
		return false;
	}
	--(building->getCountdown());
	if(building->getCountdown() <= 0 ){
		building->getCountdown() = 0;
		++counter;
		building->state = Building::state::BUILD;
		building->changeWorking(true);
		
		return true;
	}
	return false;
}

template <class T>
void BuildingManager::continueRepair( std::vector<T>& vec, Worker* worker, std::string& message ){
	for( int i = vec.size()-1; i>=0; --i ){
		if( vec[i]->state == Building::state::DAMAGED && vec[i]->getCountdown()==0 ){
			if( this->checkCost( vec[i]->getGoldRepair(), vec[i]->getLumberRepair() ) ){
				vec[i]->setLaborer( worker );
				vec[i]->getCountdown() = vec[i]->getRepairTime();
				this->subtractCost( vec[i]->getGoldRepair(), vec[i]->getLumberRepair() );
				message = "Rozpoczęto naprawdę";
				return;
			}
		}
	}
	message = "Wszystkie budynki są nieuszodzone albo już w naprawie";
}

bool BuildingManager::checkWorker( int& index , std::string& message ){
	for( int i = this->current_player->workers.size()-1; i>=0; --i ){
		if( this->current_player->workers[i]->state == Worker::state::FREE ){
			index = i;
			return true;
		}
	}
	message ="Brak wolnego pracownika";
	return false;
}

void BuildingManager::buildGoldMine( std::string& message ){
	int free_worker_index = -1;
	if( !( this->checkWorker( free_worker_index, message ) ) ){
		return;
	}
	GoldMine* new_building = new GoldMine( this->current_player->workers[free_worker_index]);
	if( checkBuild( new_building) ){
		this->current_player->goldmines.push_back( new_building );
		message = "Rozpoczęto budowe kopalni złota";
		return;
	}
	message = "Za mało surowców";
}

void BuildingManager::buildSaw( std::string& message){
	int free_worker_index = -1;
	if( !( this->checkWorker( free_worker_index, message ) ) ){
		return;
	}
	Saw* new_building = new Saw( this->current_player->workers[free_worker_index]);
	if( checkBuild( new_building) ){
		this->current_player->saws.push_back( new_building );
		message = "Rozpoczęto budowe tartaku";
		return;
	}
	message = "Za mało surowców";
}
template <class T>
bool BuildingManager::checkBuild( T new_building ){
	if( this->checkCost( new_building->getGoldCost(), new_building->getLumberCost() ) ){
		this->subtractCost( new_building->getGoldCost(), new_building->getLumberCost() );
		return true;
	}else{
		new_building->freeLaborer();
		delete new_building;
		return false;
	}
}

template <class T>
void BuildingManager::freeVector( std::vector<T>& vec ){
	for(int i = vec.size()-1; i>=0; --i){
		T tmp = vec[i];
		tmp->freeLaborer();
		vec.erase( vec.begin() + i);
		delete tmp;	
	}
}

template <class T>
void BuildingManager::countBuildings(std::vector<T> buildings, int& working, int& building, int& damaged){
	for(int i = buildings.size()-1; i>=0; --i){
		if( buildings[i]->state == Building::state::BUILD ){
			++working;
		}else if( buildings[i]->state == Building::state::NOT_BUILD ){
			++building;
		}else if( buildings[i]->state == Building::state::DAMAGED ){	
			++damaged;
		}
	}
}

void BuildingManager::getStatus( std::string name, int& working, int& building, int& damaged, std::string& message ){
	message += "\n---" + name + 
		"---\nPracujące:\t" + std::to_string(working) +
		"\nW budowie:\t" + std::to_string(building) +
		"\nZepsute:\t" +std::to_string(damaged);
}

void BuildingManager::damageRandomly( std::string& message ){
	int random = rand()%10;//10% to have goldmine destroyed
	if( random == 0 ){
		random = rand()%current_player->goldmines.size();
		if( current_player->goldmines[random]->state != Building::state::DAMAGED){
			damage(current_player->goldmines[random]);
			message += "\nAwaria: " + current_player->goldmines[random]->getName();
		}
	}
	random = rand()%20;//5%to have saw destroyed
	if( random == 0 ){
		random = rand()%current_player->saws.size();
		if( current_player->saws[random]->state != Building::state::DAMAGED){
			damage(current_player->saws[random]);
			message += "\nAwaria: " + current_player->saws[random]->getName();
		}
	}
}

