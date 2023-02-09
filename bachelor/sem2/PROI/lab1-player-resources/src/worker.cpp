#include "worker.h"

Worker::Worker(){
	countdown = TRAIN_TIME;
	state = TRAINING;
}

Worker::Worker(int i){
	countdown = 0;
	state = FREE;
}

void Worker::continueTraining(){
	if( this->state != TRAINING ){
		return;
	}
	--(this->countdown);
	if( this->countdown == 0 ){
		this->state = FREE;
	}
}
