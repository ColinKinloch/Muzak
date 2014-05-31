// Copyright © 2014 Colin Kinloch <colinmkinloch@gmail.com> - All Rights Reserved
// Licence in LICENSE

#ifndef MUZAK_MIDI
#define MUZAK_MIDI

#include <Muzak/Node.hh>
#include <map>

namespace Muzak
{
	typedef long MidiMsg;
	
	class Midi: public Node
	{
	private:
		
	public:
		Midi();
		~Midi();
		
		std::map<unsigned char, unsigned char> notes;
		
		void update();
		void addMessage(MidiMsg Message);
	};
}

#endif//MUZAK_MIDI