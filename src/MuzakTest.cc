#include <Muzak/Muzak.hh>
#include <signal.h>
#include <stdio.h>
#include <portaudio.h>
#include <portmidi.h>


int execute;
void trap(int signal){ execute = 0; }

PmStream* midi;
PmEvent buffer[1];

int main()
{
	printf("Testing Muzak\n");
	
	int err;
	err = Pm_Initialize();
	if(err != pmNoError)
	 printf("PortAudio error: %s\n", Pm_GetErrorText((PmError)err));
	err = Pa_Initialize();
	if(err != paNoError)
	 printf("PortAudio error: %s\n", Pa_GetErrorText((PaError)err));
	
	signal(SIGINT, &trap);
	execute = 1;
	while(execute)
	{
	}
	signal(SIGINT, SIG_DFL);
	printf("Shutting down!\n");
	return 0;
}