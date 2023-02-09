#include <iostream>
#include <iomanip>
#include "interface.h"

void Interface::start(){
	Logic* new_logic = new Logic();
	this->logic = new_logic;
	std::cout<<"Podaj liczbe graczy:"<<std::endl;
	int num_of_players = Interface::userInputInt();
	this->logic->startGame(num_of_players);
}

void Interface::showMenu(){
	std::cout
		<<"-------------------------------"<<std::endl
		<<"["<<MANAGE_MATERIALS	<<"]Zarządzaj osadą"<<std::endl
		<<"["<<SHOW_STATE	<<"]Wyświetl stan osady"<<std::endl
		<<"["<<END_TURN		<<"]Zakończ ture"<<std::endl
		<<"["<<LEAVE		<<"]Wyjdź z gry"<<std::endl
		<<"-------------------------------"<<std::endl;
}

void Interface::manageGame(){
	if( !(this->logic->isPlayerAvailable()) ){
		std::cout<<"Brak graczy"<<std::endl;
		return;
	}
	std::string message;
	Interface::showCosts();
	
	while(true){
		Interface::showMenu();
		int option = Interface::userInputInt();
		switch( option ){
			case Interface::MANAGE_MATERIALS:
				this->chooseAction();
				break;
			case Interface::SHOW_STATE:
				this->logic->getState(message);
				this->showAndClearMessage(message);
				break;
			case Interface::END_TURN:
				this->logic->endTurnActions();
				this->logic->switchPlayer();
				system("clear");
				std::cout<<"Gracz numer "<<this->logic->getPlayerNumber()<<std::endl;
				this->logic->startTurnActions(message);
				this->showAndClearMessage(message);
				break;
			case Interface::LEAVE:
				return;
			default:
				std::cout<<"Nie ma takiej opcji, popraw się:"<<std::endl;
				break;
		}//switch
	}//while
}

void Interface::chooseAction(){
	Interface::showManageMenu();
	std::string message;
	while(true){
		int option = Interface::userInputInt();
		switch(option){
			case Interface::BUILD:
				this->chooseBuildOrRepair( option );
				return;
			case Interface::TRAIN:
				this->logic->train(message);
				this->showAndClearMessage(message);
				return;
			case Interface::REPAIR:
				this->chooseBuildOrRepair( option );
				return;
			case Interface::LEAVE:
				std::cout<<"Anulowano"<<std::endl;
				return;
			default:
				std::cout<<"Nie ma takiej opcji, popraw się:"<<std::endl;
				break;
		}//switch
	}//while
}

void Interface::showManageMenu(){
	std::cout
				<<"Wybierz czynność"<<std::endl
		<<"["<<BUILD	<<"]Buduj"<<std::endl
		<<"["<<TRAIN	<<"]Trenuj"<<std::endl
		<<"["<<REPAIR	<<"]Napraw"<<std::endl
		<<"["<<LEAVE	<<"]Anuluj"<<std::endl;
}

void Interface::showBuildingMenu(){
	std::cout
				<<"Wybierz budynek"<<std::endl
		<<"["<<GOLD_MINE<<"]Kopalnia złota"<<std::endl
		<<"["<<SAW	<<"]Tartak"<<std::endl
		<<"["<<LEAVE	<<"]Anuluj"<<std::endl;
}

void Interface::chooseBuildOrRepair( int& action_option ){//action option decides whether to build or repair
	Interface::showBuildingMenu();
	while(true){
		std::string message;
		int option = Interface::userInputInt();
		switch(option){
			case Interface::GOLD_MINE:
				if( action_option == Interface::BUILD ){
					this->logic->buildGoldMine(message);
				}else{
					this->logic->repairGoldMine(message);
				}
				this->showAndClearMessage(message);
				return;
			case Interface::SAW:
				if( action_option == Interface::BUILD ){
					this->logic->buildSaw(message);
				}else{
					this->logic->repairSaw(message);
				}
				this->showAndClearMessage(message);
				return;
			case Interface::LEAVE:
				std::cout<<"Anulowano"<<std::endl;
				return;
			default:
				std::cout<<"Nie ma takiej opcji, popraw się:"<<std::endl;
				break;
		}//switch
	}//while
}

void Interface::end(){
	std::cout<<"Koniec gry, do zobaczenia"<<std::endl;
	this->logic->endGame();
	delete this->logic;
}

int Interface::userInputInt(){
	int input;
	std::cin>>input;

	while(std::cin.fail()){
		std::cin.clear();
		std::cin.ignore();
		std::cin>>input;
	}

	std::cin.clear();
	return input;
}

void Interface::showAndClearMessage(std::string& message){
	std::cout<<message<<std::endl;
	message = "";
}

void Interface::showCosts(){
	std::cout<<std::left<<std::setw(15)<<"Nazwa"<<" - złoto - drewno"<<std::endl;
	std::cout<<std::left<<std::setw(16)<<GoldMine::getName()<<" - "<<GoldMine::getGoldCost()<<" - "<<GoldMine::getLumberCost()<<std::endl;//16 to make it straight, probably problem with polish letters
	std::cout<<std::left<<std::setw(15)<<Saw::getName()<<" - "<<Saw::getGoldCost()<<" - "<<Saw::getLumberCost()<<std::endl;
	std::cout<<std::left<<std::setw(15)<<Worker::getName()<<" - "<<Worker::getGoldCost()<<" - "<<Worker::getLumberCost()<<std::endl;
}

