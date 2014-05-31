// Copyright © 2014 Colin Kinloch <colinmkinloch@gmail.com> - All Rights Reserved
// Licence in LICENSE

#ifndef MUZAK_INSTRUMENT
#define MUZAK_INSTRUMENT

#include <Muzak/Node.hh>
#include <Muzak/Generator.hh>
#include <Muzak/Midi.hh>
#include <math.h>

namespace Muzak
{
	class Instrument: public Node
	{
	private:
		Wave type;
		Generator gen;
		double tuning = 440;
		
		float* currBuff;
		unsigned long currSize;
		
		float midiToFreq(unsigned char note);
	public:
		Instrument();
		Instrument(Wave Type);
		Instrument(Wave Type, double Rate);
		~Instrument();
		
		void tune(double Frequency);
		void update(double t, long frames);
	};
}

#endif//MUZAK_INSTRUMENT