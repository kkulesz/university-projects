#include "worker_manager.h"

void WorkerManager::clearMemory(){
	for(int i = current_player->workers.size()-1; i>=0; --i){
		Worker* tmp = current_player->workers[i];
		current_player->workers.erase( current_player->workers.begin() + i);
		delete tmp;	
	}
}

void WorkerManager::train( std::string& message ){
	Worker* new_worker = new Worker();
	if( checkCost( new_worker->getGoldCost(), new_worker->getLumberCost() ) ){
		this->current_player->workers.push_back( new_worker );
		this->subtractCost( new_worker->getGoldCost(), new_worker->getLumberCost() );
		message = "Rozpoczęto trening pracownika";
	}else{
		delete new_worker;
		message = "Za mało surowców";
	}
}

void WorkerManager::getWorkers(std::string& message){
	int free=0;
	int busy=0;
	int training=0;
	for( int i = current_player->workers.size()-1; i>=0; --i ){
		if( current_player->workers[i]->state == Worker::state::FREE ){
			++free;
		}else if(current_player->workers[i]->state == Worker::state::BUSY){
			++busy;
		}else{
			++training;
		}
	}
	message += "\n---Pracownicy---\nWolni:  \t" + std::to_string(free) + "\nZajęci: \t" + std::to_string(busy) + "\nSzkolacy się:\t" + std::to_string(training);
}

void WorkerManager::endTurn(){

}
void WorkerManager::startTurn(std::string& message){
	int finished_workers = 0;
	for( int i = current_player->workers.size()-1; i>=0; --i ){
		this->continueTraining(current_player->workers[i], finished_workers);
	}
	if( finished_workers > 0 ){
		message = "Zakończono szkolenie pracowników - " + std::to_string(finished_workers);
	}
}

bool WorkerManager::continueTraining( Worker* worker, int& finished_workers ){
	if( worker->state != Worker::state::TRAINING ){
		return true;
	}
	--worker->getCountdown();
	if( worker->getCountdown() <= 0 ){
		++finished_workers;
		worker->state = Worker::state::FREE;
		return true;
	}
	return false;

}
