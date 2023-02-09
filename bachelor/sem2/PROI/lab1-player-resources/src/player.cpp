#include <iostream>
#include <cstdlib>
#include <ctime>

#include "player.h"


Player::Player(): gold(200), lumber(100){
	Worker* to_mine = new Worker(0);
	Worker* to_saw = new Worker(0);
	Worker* free = new Worker(0);
	this->workers.push_back(to_mine);
	this->workers.push_back(to_saw);
	this->workers.push_back(free);

	GoldMine* first_goldmine = new GoldMine( to_mine, 0 );
	Saw* first_saw = new Saw( to_saw, 0 );
	this->goldmines.push_back( first_goldmine );
	this->saws.push_back( first_saw );
}

void Player::addGold(int const new_gold){
	this->gold += new_gold;
}
void Player::addLumber(int const new_lumber){
	this->lumber += new_lumber;
}
