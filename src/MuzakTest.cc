#include <portaudio.h>
#include <portmidi.h>

PmStream* midi;
PmEvent buffer[1];

int main()
{
	TIME_START;
	
	Pm_initialize();
	
	return 0;
}