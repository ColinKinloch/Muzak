#include <Muzak/Muzak.hh>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <portaudio.h>
#include <portmidi.h>

#define TABLE_SIZE (200)

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER paFramesPerBufferUnspecified
#define OUTPUT_DEVICE Pa_GetDefaultOutputDevice()
#define INPUT_DEVICE Pm_GetDefaultInputDeviceID()

float masterVolume = 0.2f;
int timeVal=0;
int execute;
void exitTrap(int signal){ execute = 0; }

typedef struct
{
	float sine[TABLE_SIZE];
	float left_phase;
	float right_phase;
	int n;
}
paTestData;

typedef struct
{
}
audioData;

int midiID;
PmStream* midiStream;
#define EVENTLENGTH 1
PmEvent midiEvent[EVENTLENGTH];

PaDeviceIndex audioID;
const PaDeviceInfo* audioDeviceInfo;
PaStream* audioStream;
PaStreamParameters audioOutP;
PaStreamInfo audioStreamInfo;

Muzak::Instrument trumpette = Muzak::Instrument(Muzak::Wave::SAWTOOTH, SAMPLE_RATE);
Muzak::Instrument sine = Muzak::Instrument(Muzak::Wave::SINE, SAMPLE_RATE);
Muzak::Midi midiNode = Muzak::Midi();
Muzak::Mixer outputNode = Muzak::Mixer();

void midiRead();
void optHandle(int argc, char** argv);
int audioCallback (const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
 const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

int main(int argc, char** argv)
{
	std::cout<<"--Testing Muzak--"<<std::endl<<std::endl;
	
	trumpette.addInput(&midiNode);
	sine.addInput(&midiNode);
	//outputNode.addInput(&trumpette);
	outputNode.addInput(&sine);
	
	midiID = INPUT_DEVICE;
	audioID = OUTPUT_DEVICE;
	
	optHandle(argc, argv);
	
	int err;
	err = Pm_Initialize();
	if(err != pmNoError)
	 std::cout<<"PortMidi error: "<<Pm_GetErrorText((PmError)err)<<std::endl;
	err = Pa_Initialize();
	if(err != paNoError)
	 std::cout<<"PortAudio error: "<<Pa_GetErrorText((PaError)err)<<std::endl;
	
	
	//PortMidi
	std::cout<<"Available MIDI devices:"<<std::endl;
	int numDev = Pm_CountDevices();
	for(int i=0; i<numDev; i++)
	{
		const PmDeviceInfo* tempInfo = Pm_GetDeviceInfo(i);
		
		if(midiID==i)
		 printf(">");
		else
		 printf(" ");
		
		if(tempInfo->input)
		 printf("Input:  ");
		else if(tempInfo->output)
		 printf("Output: ");
		else
		 printf("Unknown:");
		printf("%s\n", tempInfo->name);
	}
	Pm_OpenInput(&midiStream, midiID, NULL, 128, NULL, NULL);
	std::cout<<std::endl;
	
	paTestData data;
	data.left_phase = data.right_phase = 0.0;
	data.n = 0;
	
	for( int i=0; i<TABLE_SIZE; i++ )
	 data.sine[i] = (float) (1.f * sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. ));
	
	std::cout<<"Available audio devices:"<<std::endl;
	numDev = Pa_GetDeviceCount();
	if(audioID==-1)
	 std::cout<<">";
	else
	 std::cout<<" ";
	std::cout<<"No Device"<<std::endl;
	for(int i=0; i<numDev; i++)
	{
		const PaDeviceInfo* tempInfo = Pa_GetDeviceInfo(i);
		
		if(audioID==i)
		 std::cout<<">";
		else
		 std::cout<<" ";
		
		std::cout<<tempInfo->name<<std::endl;
	}
	
	audioDeviceInfo = Pa_GetDeviceInfo(audioID);
	
	//PortAudio
	audioOutP.device = Pa_GetDefaultOutputDevice();
	audioOutP.channelCount = 2;
	audioOutP.sampleFormat = paFloat32;
	audioOutP.suggestedLatency = Pa_GetDeviceInfo(audioOutP.device)->defaultLowOutputLatency;
	Pa_OpenDefaultStream(&audioStream, 0, 2, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, audioCallback, &data);
	
	
	Pa_StartStream(audioStream);
	
	signal(SIGINT, &exitTrap);
	execute = 1;
	
	const PaStreamInfo* streamInfo = Pa_GetStreamInfo(audioStream);
	outputNode.setRate(streamInfo->sampleRate);
	
	while(execute)
	{
		if(Pm_Poll(midiStream))
		 midiRead();
		midiNode.update();
	}
	printf("Shutting down!\n");
	signal(SIGINT, SIG_DFL);
	
	Pa_StopStream(audioStream);
	Pa_CloseStream(audioStream);
	Pm_Close(midiStream);
	
	Pa_Terminate();
	Pm_Terminate();
	
	return 0;
}

void optHandle(int argc, char** argv)
{
	int c;
	while((c = getopt(argc, argv, "i:o:")) != -1)
	{
		switch(c)
		{
			std::cout<<"fart"<<std::endl;
			case 'i':
			{
				midiID=atoi(optarg);
				std::cout<<"Selecting midi: "<<midiID<<std::endl;
				break;
			}
			case 'o':
			{
				audioID=atoi(optarg);
				std::cout<<"Selecting audio: "<<audioID<<std::endl;
				break;
			}
		}
	}
}

void midiRead()
{
	Pm_Read(midiStream, midiEvent, EVENTLENGTH);
	for(int i = 0; i<EVENTLENGTH; i++)
	 midiNode.addMessage((Muzak::MidiMsg)midiEvent[i].message);
}

int audioCallback (const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
 const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	// Cast data passed through stream to our structure. 
	paTestData *data = (paTestData*)userData;
	float *out = (float*)outputBuffer;
	(void) inputBuffer; // Prevent unused variable warning.
	
	outputNode.update(timeInfo->outputBufferDacTime, framesPerBuffer);
	
	float freq = 440.f;
	
	for(int i=0; i<framesPerBuffer; i++)
	{
		data->n++;
		double dt = framesPerBuffer/44100.f;
		double lt = i/(float)framesPerBuffer;
		//lt *= freq;
		*out++ = data->sine[data->n%TABLE_SIZE];  // left
		*out++ = data->right_phase;  // right
		//square
		//std::cout<<out<<std::endl;
		//data->right_phase = (2*floor(lt)-floor(2*lt)+1)*2-1.f;
		//sawtooth
		//data->right_phase = (lt-floor(lt))*2-1.f;
		//sine
		//data->right_phase = sin(2*M_PI*lt);
		
		data->right_phase = outputNode.buffer[data->n%framesPerBuffer];
		
		data->right_phase *= masterVolume;
	}
	
	return 0;
}
int paCB(const void *inBuff, void *outBuff, unsigned long fpb,
 const PaStreamCallbackTimeInfo *time, PaStreamCallbackFlags status, void *data)
{
	audioData *userData = (audioData*)data;
	float *out = (float*)outBuff;
}