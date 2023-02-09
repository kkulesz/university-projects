#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <math.h>
#include "../../include/alsa.h"

#include <cstdlib>
#include <alsa/asoundlib.h>

#define BUFFER_SIZE 32768
#define ALSA_PCM_NEW_HW_PARAMS_API

//wrzucam tutaj żeby się nie zgubiło jak coś nie będzie działać xd
//Some ALSA library functions use the dlopen function and floating-point operations, so you also may need to add -ldl and -lm.

int spawn(const char * program, char ** arg_list) {
	pid_t child_pid = fork();
	if (child_pid != 0)
		return child_pid;      /* This is the parent process.  */
	else {

		execvp (program, arg_list);     /* Now execute PROGRAM */
		fprintf (stderr, "An error occurred in execvp\n");
		abort ();
	}
}


void f1();
void f2();
void f3();
void f4();

int main(int argc, char** argv) {

//	const char* argListC[1];
//	argListC[0] = std::to_string(BUFFER_SIZE).c_str();
//	char* argList[1];
//	memcpy(argList[0],argListC[0], sizeof(char)*BUFFER_SIZE);

	spawn("./supplier", nullptr);
	spawn("./voiceChanger", nullptr);
	spawn("./consumer", nullptr);

	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(1, &set);
	sched_setaffinity(0, sizeof(set), &set);

	printf("CPU main: %i\n", sched_getcpu());







//
//
//	for(int i=0; i < 2; i++){
//		alsaRead(buf);
//
//		sleep(1);
//
//		alsaWrite(buf);
//	}

// FOR LEARNING AND TESTING
    //f1();
    //f2();
    //f3(); // run executable with "./supervisor < /dev/urandom" PRZYCISZ SŁUCHAWKI!
    //f4();

    //jak daję  "./supervisor 2 > tmp.raw " a potem "./supervisor 1 < tmp.raw" to ładnie odtwarza 5 sekund nagranego dźwięku
//    if (!strcmp(argv[1], "1")){
//        f3();
//    }else if (!strcmp(argv[1], "2")){
//        f4();
//    }

	return 0;
}

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

//przyklady ze strony https://www.linuxjournal.com/article/6735?fbclid=IwAR01j8BJ87xzcj3FR9YKhJ1EVNhRelNLBO5GTkxLkY-Hq-WePJ8M1GioAGY

//wypisuje parametry
void f1(){
    int val;

    printf("ALSA library version: %s\n",
           SND_LIB_VERSION_STR);

    printf("\nPCM stream types:\n");
    for (val = 0; val <= SND_PCM_STREAM_LAST; val++)
        printf("  %s\n",
               snd_pcm_stream_name((snd_pcm_stream_t)val));

    printf("\nPCM access types:\n");
    for (val = 0; val <= SND_PCM_ACCESS_LAST; val++)
        printf("  %s\n",
               snd_pcm_access_name((snd_pcm_access_t)val));

    printf("\nPCM formats:\n");
    for (val = 0; val <= SND_PCM_FORMAT_LAST; val++)
        if (snd_pcm_format_name((snd_pcm_format_t)val)
            != NULL)
            printf(" %d  %s (%s)\n",
                   val,
                   snd_pcm_format_name((snd_pcm_format_t)val),
                   snd_pcm_format_description( (snd_pcm_format_t)val) );

    printf("\nPCM subformats:\n");
    for (val = 0; val <= SND_PCM_SUBFORMAT_LAST;
         val++)
        printf("  %s (%s)\n",

               snd_pcm_subformat_name((snd_pcm_subformat_t)val),
               snd_pcm_subformat_description((snd_pcm_subformat_t)val));

    printf("\nPCM states:\n");
    for (val = 0; val <= SND_PCM_STATE_LAST; val++)
        printf("  %s\n",
               snd_pcm_state_name((snd_pcm_state_t)val));

}
//ustawia i wypisuje wiecej parametrów
void f2(){
    int rc;
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    unsigned int val, val2;
    int dir;
    snd_pcm_uframes_t frames;

    /* Open PCM device for playback. */
    rc = snd_pcm_open(&handle, "plughw:0,0",
                      SND_PCM_STREAM_PLAYBACK, 0);
    if (rc < 0) {
        fprintf(stderr,
                "unable to open pcm device: %s\n",
                snd_strerror(rc));
        exit(1);
    }

    /* Allocate a hardware parameters object. */
    snd_pcm_hw_params_alloca(&params);

    /* Fill it in with default values. */
    snd_pcm_hw_params_any(handle, params);

    /* Set the desired hardware parameters. */

    /* Interleaved mode */
    snd_pcm_hw_params_set_access(handle, params,
                                 SND_PCM_ACCESS_RW_INTERLEAVED);

    /* Signed 16-bit little-endian format */
    snd_pcm_hw_params_set_format(handle, params,
                                 SND_PCM_FORMAT_S16_LE);

    /* Two channels (stereo) */
    snd_pcm_hw_params_set_channels(handle, params, 2);

    /* 44100 bits/second sampling rate (CD quality) */
    val = 44100;
    snd_pcm_hw_params_set_rate_near(handle,
                                    params, &val, &dir);

    /* Write the parameters to the driver */
    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0) {
        fprintf(stderr,
                "unable to set hw parameters: %s\n",
                snd_strerror(rc));
        exit(1);
    }

    /* Display information about the PCM interface */

    printf("PCM handle name = '%s'\n",
           snd_pcm_name(handle));

    printf("PCM state = %s\n",
           snd_pcm_state_name(snd_pcm_state(handle)));

    snd_pcm_hw_params_get_access(params,(snd_pcm_access_t *) &val);
    printf("access type = %s\n",
           snd_pcm_access_name((snd_pcm_access_t)val));
//XD dziala BYLO WCZEŚNIEJ snd_pcm_hw_params_get_format(params, &val); ALE SIE NIE KOMPILOWALO
    snd_pcm_hw_params_get_format(params, (snd_pcm_format_t*)&val);
    printf("format = '%s' (%s)\n",
           snd_pcm_format_name((snd_pcm_format_t)val),
           snd_pcm_format_description((snd_pcm_format_t)val));

    snd_pcm_hw_params_get_subformat(params,
                                    (snd_pcm_subformat_t *)&val);
    printf("subformat = '%s' (%s)\n",
           snd_pcm_subformat_name((snd_pcm_subformat_t)val),
           snd_pcm_subformat_description(
                   (snd_pcm_subformat_t)val));

    snd_pcm_hw_params_get_channels(params, &val);
    printf("channels = %d\n", val);

    snd_pcm_hw_params_get_rate(params, &val, &dir);
    printf("rate = %d bps\n", val);

    snd_pcm_hw_params_get_period_time(params,
                                      &val, &dir);
    printf("period time = %d us\n", val);

    snd_pcm_hw_params_get_period_size(params,
                                      &frames, &dir);
    printf("period size = %d frames\n", (int)frames);

    snd_pcm_hw_params_get_buffer_time(params,
                                      &val, &dir);
    printf("buffer time = %d us\n", val);

    snd_pcm_hw_params_get_buffer_size(params,
                                      (snd_pcm_uframes_t *) &val);
    printf("buffer size = %d frames\n", val);

    snd_pcm_hw_params_get_periods(params, &val, &dir);
    printf("periods per buffer = %d frames\n", val);

    snd_pcm_hw_params_get_rate_numden(params,
                                      &val, &val2);
    printf("exact rate = %d/%d bps\n", val, val2);

    val = snd_pcm_hw_params_get_sbits(params);
    printf("significant bits = %d\n", val);

    snd_pcm_hw_params_get_tick_time(params,
                                    &val, &dir);
    printf("tick time = %d us\n", val);

    val = snd_pcm_hw_params_is_batch(params);
    printf("is batch = %d\n", val);

    val = snd_pcm_hw_params_is_block_transfer(params);
    printf("is block transfer = %d\n", val);

    val = snd_pcm_hw_params_is_double(params);
    printf("is double = %d\n", val);

    val = snd_pcm_hw_params_is_half_duplex(params);
    printf("is half duplex = %d\n", val);

    val = snd_pcm_hw_params_is_joint_duplex(params);
    printf("is joint duplex = %d\n", val);

    val = snd_pcm_hw_params_can_overrange(params);
    printf("can overrange = %d\n", val);

    val = snd_pcm_hw_params_can_mmap_sample_resolution(params);
    printf("can mmap = %d\n", val);

    val = snd_pcm_hw_params_can_pause(params);
    printf("can pause = %d\n", val);

    val = snd_pcm_hw_params_can_resume(params);
    printf("can resume = %d\n", val);

    val = snd_pcm_hw_params_can_sync_start(params);
    printf("can sync start = %d\n", val);

    snd_pcm_close(handle);

}
//czyta standardowe wejscie i je odtwarza
void f3(){
    long loops;
    int rc;
    int size;
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    unsigned int val;
    int dir;
    snd_pcm_uframes_t frames;
    char *buffer;

    /* Open PCM device for playback. */
    rc = snd_pcm_open(&handle, "plughw:0,0",
                      SND_PCM_STREAM_PLAYBACK, 0);
    if (rc < 0) {
        fprintf(stderr,
                "unable to open pcm device: %s\n",
                snd_strerror(rc));
        exit(1);
    }

    /* Allocate a hardware parameters object. */
    snd_pcm_hw_params_alloca(&params);

    /* Fill it in with default values. */
    snd_pcm_hw_params_any(handle, params);

    /* Set the desired hardware parameters. */

    /* Interleaved mode */
    snd_pcm_hw_params_set_access(handle, params,
                                 SND_PCM_ACCESS_RW_INTERLEAVED);

    /* Signed 16-bit little-endian format */
    snd_pcm_hw_params_set_format(handle, params,
                                 SND_PCM_FORMAT_S16_LE);

    /* Two channels (stereo) */
    snd_pcm_hw_params_set_channels(handle, params, 2);

    /* 44100 bits/second sampling rate (CD quality) */
    val = 44100;
    snd_pcm_hw_params_set_rate_near(handle, params,
                                    &val, &dir);

    /* Set period size to 32 frames. */
    frames = 32;
    snd_pcm_hw_params_set_period_size_near(handle,
                                           params, &frames, &dir);

    /* Write the parameters to the driver */
    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0) {
        fprintf(stderr,
                "unable to set hw parameters: %s\n",
                snd_strerror(rc));
        exit(1);
    }

    /* Use a buffer large enough to hold one period */
    snd_pcm_hw_params_get_period_size(params, &frames,
                                      &dir);
    size = frames * 4; /* 2 bytes/sample, 2 channels */
    buffer = (char *) malloc(size);

    /* We want to loop for 5 seconds */
    snd_pcm_hw_params_get_period_time(params,
                                      &val, &dir);
    /* 5 seconds in microseconds divided by
     * period time */
    loops = 5000000 / val;

    while (loops > 0) {
        loops--;
        rc = read(0, buffer, size);
        if (rc == 0) {
            fprintf(stderr, "end of file on input\n");
            break;
        } else if (rc != size) {
            fprintf(stderr,
                    "short read: read %d bytes\n", rc);
        }
        rc = snd_pcm_writei(handle, buffer, frames);
        //snd_pcm_prepare(handle);

        if (rc == -EPIPE) {
            // EPIPE means underrun
            fprintf(stderr, "underrun occurred\n");
            snd_pcm_prepare(handle);
        } else if (rc < 0) {
            fprintf(stderr,
                    "error from writei: %s\n",
                    snd_strerror(rc));
        }  else if (rc != (int)frames) {
            fprintf(stderr,
                    "short write, write %d frames\n", rc);
        }
    }

    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(buffer);
}
//sczytuje domyslne urzadzenie glosowe i ja wypisuje na standardowe wyjście
void f4(){
    long loops;
    int rc;
    int size;
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    unsigned int val;
    int dir;
    snd_pcm_uframes_t frames;
    char *buffer;

    /* Open PCM device for recording (capture). */
    rc = snd_pcm_open(&handle, "plughw:0,0",
                      SND_PCM_STREAM_CAPTURE, 0);
    if (rc < 0) {
        fprintf(stderr,
                "unable to open pcm device: %s\n",
                snd_strerror(rc));
        exit(1);
    }

    /* Allocate a hardware parameters object. */
    snd_pcm_hw_params_alloca(&params);

    /* Fill it in with default values. */
    snd_pcm_hw_params_any(handle, params);

    /* Set the desired hardware parameters. */

    /* Interleaved mode */
    snd_pcm_hw_params_set_access(handle, params,
                                 SND_PCM_ACCESS_RW_INTERLEAVED);

    /* Signed 16-bit little-endian format */
    snd_pcm_hw_params_set_format(handle, params,
                                 SND_PCM_FORMAT_S16_LE);

    /* Two channels (stereo) */
    snd_pcm_hw_params_set_channels(handle, params, 2);

    /* 44100 bits/second sampling rate (CD quality) */
    val = 44100;
    snd_pcm_hw_params_set_rate_near(handle, params,
                                    &val, &dir);

    /* Set period size to 32 frames. */
    frames = 32;
    snd_pcm_hw_params_set_period_size_near(handle,
                                           params, &frames, &dir);

    /* Write the parameters to the driver */
    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0) {
        fprintf(stderr,
                "unable to set hw parameters: %s\n",
                snd_strerror(rc));
        exit(1);
    }

    /* Use a buffer large enough to hold one period */
    snd_pcm_hw_params_get_period_size(params,
                                      &frames, &dir);
    size = frames * 4; /* 2 bytes/sample, 2 channels */
    buffer = (char *) malloc(size);

    /* We want to loop for 5 seconds */
    snd_pcm_hw_params_get_period_time(params,
                                      &val, &dir);
    loops = 5000000 / val;

    while (loops > 0) {
        loops--;
        rc = snd_pcm_readi(handle, buffer, frames);
        if (rc == -EPIPE) {
            /* EPIPE means overrun */
            fprintf(stderr, "overrun occurred\n");
            snd_pcm_prepare(handle);
        } else if (rc < 0) {
            fprintf(stderr,
                    "error from read: %s\n",
                    snd_strerror(rc));
        } else if (rc != (int)frames) {
            fprintf(stderr, "short read, read %d frames\n", rc);
        }
        applyeffect(buffer,2);
        rc = write(1, buffer, size);
        if (rc != size)
            fprintf(stderr,
                    "short write: wrote %d bytes\n", rc);
    }

    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(buffer);

}