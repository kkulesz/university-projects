//
// Created by demongo on 31.10.2020.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include "../../include/alsa.h"

int main(int argc, char** argv) {
	std::cout << "Consumer!" << std::endl;

	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(2, &set);
	sched_setaffinity(0, sizeof(set), &set);

	printf("CPU consumer: %i\n", sched_getcpu());


	// ftok to generate unique key
	key_t key = ftok("shmfile",65);

	// shmget returns an identifier in shmid
	int shmid = shmget(key, BUFFER_SIZE,0666|IPC_CREAT);

	// shmat to attach to shared memory
	short *str = (short*) shmat(shmid,(void*)0,0);

	sleep(5);

	short nBuf[BUFFER_SIZE];

	memcpy(nBuf, str, BUFFER_SIZE);

	alsaWrite(nBuf);

	shmdt(str);

	return 0;
}