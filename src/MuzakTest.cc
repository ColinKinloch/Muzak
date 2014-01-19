#include <Muzak/Muzak.hh>
#include <signal.h>
#include <stdio.h>
#include <portaudio.h>
#include <portmidi.h>

int i=0;
int execute;
void trap(int signal){ execute = 0; }

PmStream* midiStream;
PmTimeProcPtr midiTime;
PmTimeProcPtr midiTimestamp;
PmEvent buffer[1];

void midiRead()
{
}

int main()
{
	printf("Testing Muzak\n");
	
	int err;
	err = Pm_Initialize();
	if(err != pmNoError)
	 printf("PortMidi error: %s\n", Pm_GetErrorText((PmError)err));
	err = Pa_Initialize();
	if(err != paNoError)
	 printf("PortAudio error: %s\n", Pa_GetErrorText((PaError)err));
	
	const PmDeviceInfo* midiDevice = Pm_GetDeviceInfo(i);
	printf("Input: %s\n", midiDevice->name);
	Pm_OpenInput(&midiStream, i, NULL, 128, NULL, NULL);
	
	signal(SIGINT, &trap);
	execute = 1;
	while(execute)
	{
		midiRead();
	}
	printf("Shutting down!\n");
	signal(SIGINT, SIG_DFL);
	
	Pm_Close(midiStream);
	
	Pa_Terminate();
	Pm_Terminate();
	
	
	return 0;
}