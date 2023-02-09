#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "logic.h"

class Interface{
public:
	void start();
	void manageGame();
	void end();
	void chooseAction();
	void chooseBuildOrRepair( int& action_option );
	void showAndClearMessage(std::string& message);
private:
	Logic* logic;

	static int userInputInt();
	static void showMenu();
	static void showManageMenu();
	static void showBuildingMenu();
	static void showCosts();

//main menu
	static const int MANAGE_MATERIALS = 1;
	static const int SHOW_STATE = 2;
	static const int END_TURN = 3;
	static const int LEAVE = 0;

//manage menu
	static const int BUILD = 1;
	static const int TRAIN = 2;
	static const int REPAIR = 3;
//building menu
	static const int GOLD_MINE = BuildingManager::GOLDMINE;
	static const int SAW = BuildingManager::SAW;
};

#endif
