#include "goldmine.h"

GoldMine::GoldMine( Worker* worker, int i){//special constructor for game start
	state = BUILD;
	is_working = true;
	countdown = 0;
	laborer = worker;
	worker->state = Worker::state::BUSY;
}

GoldMine::GoldMine( Worker* worker ){
	state = NOT_BUILD;
	is_working = false;
	countdown = BUILD_TIME;
	laborer = worker;
	worker->state = Worker::state::BUSY;
}

int const GoldMine::getProduction(){
	if( this->state == BUILD && this->is_working ){
		return this->GOLD_PRODUCTION;
	}else{
		return 0;
	}
}




