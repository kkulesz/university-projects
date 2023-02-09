//
// Created by demongo on 20.11.2020.
//

#ifndef SCZR_VOICECHANGERSYSTEM_ALSA_H
#define SCZR_VOICECHANGERSYSTEM_ALSA_H

#include <cstdlib>
#include <alsa/asoundlib.h>
#define BUFFER_SIZE 32768

void alsaWrite(short *buf);

void alsaRead(short *buf);

#endif //SCZR_VOICECHANGERSYSTEM_ALSA_H
