#include <Muzak/Muzak.hh>
#include <signal.h>
#include <stdio.h>
#include <portaudio.h>
#include <portmidi.h>

int i=0;
int execute;
void trap(int signal){ execute = 0; }

PmStream* midiStream;
#define EVENTLENGTH 1
PmEvent midiEvent[EVENTLENGTH];

void midiRead()
{
	Pm_Read(midiStream, midiEvent, EVENTLENGTH);
	long msg, msg1, msg2, msg3;
	for(int i = 0; i<EVENTLENGTH; i++)
	{
		msg = midiEvent[i].message;
		msg1 = msg&0x0000ff;
		msg2 = (msg&0x00ff00)/0x100;
		msg3 = (msg&0xff0000)/0x10000;
		
		
		switch(msg1)
		{
			case 0x90:
			{
				if(msg3==0x00)
				 printf("%lX: off\n", msg2);
				else
				 printf("%lX: on at %li\n", msg2, msg3);
				break;
			}
			case 0x80:
			{
				printf("%lX: off\n", msg2);
				break;
			}
			case 0xe0:
			{
				printf("pitch at %li\n", msg3);
				break;
			}
			case 0xb0:
			{
				printf("mod at %li\n", msg3);
				break;
			}
		}
	}
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
	
	int midiNumDev = Pm_CountDevices();
	const PmDeviceInfo* midiDevice = Pm_GetDeviceInfo(i);
	printf("Input: %s\n", midiDevice->name);
	Pm_OpenInput(&midiStream, i, NULL, 128, NULL, NULL);
	//Pm_SetFilter(midiStream, PM_FILT_ACTIVE|PM_FILT_CLOCK);
	
	signal(SIGINT, &trap);
	execute = 1;
	while(execute)
	{
		if(Pm_Poll(midiStream))
		 midiRead();
	}
	printf("Shutting down!\n");
	signal(SIGINT, SIG_DFL);
	
	Pm_Close(midiStream);
	
	Pa_Terminate();
	Pm_Terminate();
	
	
	return 0;
}