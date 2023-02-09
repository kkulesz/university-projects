#include "buildings.h"

Worker* Building::freeLaborer(){	
	Worker* tmp = this->laborer;
	if( tmp ){
		tmp->state = Worker::state::FREE;
	}
	this->laborer = nullptr;
	return tmp;
}

Worker* Building::setLaborer( Worker* new_laborer){
	Worker* tmp = this->freeLaborer();
	this->laborer = new_laborer;
	new_laborer->state = Worker::state::BUSY;	
	return tmp;
}
