#include "interface.h"

int main(){
	srand(time(NULL));

	Interface uif;
	uif.start();
	uif.manageGame();
	uif.end();
	return 0;
}

