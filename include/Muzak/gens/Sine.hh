// Copyright © 2014 Colin Kinloch <colinmkinloch@gmail.com> - All Rights Reserved
// Licence in LICENSE

#ifndef MUZAK_SINE
#define MUZAK_SINE

#include <Muzak/Node.hh>
#include <random>
#include <cmath>
//chrono?
#include <ctime>

namespace Muzak
{
	namespace gens
	{
		enum class Wave{TRIANGLE, SAWTOOTH, SQUARE, NOISE, DIRTY, SINE, HALFSINE, MODSINE, SINETOOTH};
		
		class Sine
		{
		private:
			unsigned long size;
			float* buffer;
		public:
			Sine(unsigned int Length);
			~Sine();
			
			float* makeFloat();
		};
	}
}

#endif//MUZAK_SINE