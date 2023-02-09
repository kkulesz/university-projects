//
// Created by demongo on 31.10.2020.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <math.h>
#include "../../include/alsa.h"


float lfo,dlfo,fs,fc,BW,C,D,a0,a1,a2,b1,b2,*x[3],*y[3];
int channels = 2;
#define FILTERSWEEP_LFO_CENTER 2000.
#define FILTERSWEEP_LFO_DEPTH 1800.
#define FILTERSWEEP_LFO_FREQ 0.2
#define FILTER_BANDWIDTH 50

void applyeffect(char *buffer, int r) {
	short *samples = (short *) buffer;
	int i;
	for (i = 0; i < r; i++) {
		int chn;

		fc = sin(lfo) * FILTERSWEEP_LFO_DEPTH + FILTERSWEEP_LFO_CENTER;
		lfo += dlfo;
		if (lfo > 2. * M_PI) lfo -= 2. * M_PI;
		C = 1. / tan(M_PI * BW / fs);
		D = 2. * cos(2 * M_PI * fc / fs);
		a0 = 1. / (1. + C);
		a1 = 0;
		a2 = -a0;
		b1 = -C * D * a0;
		b2 = (C - 1) * a0;

		for (chn = 0; chn < channels; chn++) {
			x[chn][2] = x[chn][1];
			x[chn][1] = x[chn][0];

			y[chn][2] = y[chn][1];
			y[chn][1] = y[chn][0];

			x[chn][0] = samples[i * channels + chn];
			y[chn][0] = a0 * x[chn][0] + a1 * x[chn][1] + a2 * x[chn][2]
						- b1 * y[chn][1] - b2 * y[chn][2];
			samples[i * channels + chn] = y[chn][0];
		}
	}
}

int main(int argc, char** argv) {
	std::cout << "VoiceChanger!" << std::endl;

	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(2, &set);
	sched_setaffinity(0, sizeof(set), &set);

	printf("CPU voice: %i\n", sched_getcpu());

	return 0;
}