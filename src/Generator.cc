// Copyright © 2014 Colin Kinloch <colinmkinloch@gmail.com> - All Rights Reserved
// Licence in LICENSE

#include <Muzak/Generator.hh>
#include <iostream>

Muzak::Generator::Generator(): Muzak::Generator::Generator(Muzak::Wave::TRIANGLE)
{}
Muzak::Generator::Generator(Wave Type): Muzak::Generator::Generator(Type, 44100.f)
{}
Muzak::Generator::Generator(Wave Type, double Rate): sine(512)
{
	size = 0;
	m = 0;
	buffer = new float[size];
	type = Type;
	rate = Rate;
	
}
Muzak::Generator::~Generator()
{
	//delete buffer;
}

float* Muzak::Generator::makeFloat(float freq, double t, unsigned long frames)
{
	if(size<frames)
	{
		delete buffer;
		size = frames;
		buffer = new float[size];
	}
	double dt = frames/(float)rate; //Time per frame
	switch(type)
	{
		case Muzak::Wave::SINE:
		{
			for( int i=0; i<frames; i++ )
			{
				double lt = i/(double)frames; //i*dt+t;
				lt *= freq;
				buffer[i] = sine.makeFloat()[i];
			}
			break;
		}
		case Muzak::Wave::SAWTOOTH:
		{
			for(int i=0; i<frames; i++)
			{
				//QUE!?
				//TODO work it out
				double lt = i/(double)frames;
				lt *= freq;
				buffer[i] = (lt-floor(lt))*2-1.f;
				/*
				if(i==0)
				printf("%f", lt);
				if(i==63)
				printf("-%f\n", lt);
				*/
				//buffer[i] = (float)((((int)((t*i)+dt))%(int)freq)/(freq/2))-1.f;
			}
			break;
		}
		case Muzak::Wave::SQUARE:
		{
			for(int i=0; i<frames; i++)
			{
				double lt = i/(double)frames; //i*dt+t;
				//lt *= freq;
				
				buffer[i] = (float)(((int)floor((dt)/freq)%2))*2-1.f;
				//buffer[i] = (int)floor(dt*10/freq)%2*2-1.f;
				
				//buffer[i] = (2*floor(lt)-floor(2*lt)+1)*2-1.f;
				
				if(i==0);
				//printf("%f\n", buffer[i]);
			}
			break;
		}
		case Muzak::Wave::NOISE:
		{
			for(int i=0; i<frames; i++)
			{
				buffer[i] = uniform(rng);
			}
			break;
		}
	}
	
	return buffer;
}