// Copyright © 2014 Colin Kinloch <colinmkinloch@gmail.com> - All Rights Reserved
// Licence in LICENSE

#ifndef MUZAK_NODE
#define MUZAK_NODE

#include <vector>
#include <queue>

namespace Muzak
{
	enum class MsgType {
		Midi,
		Note,
		Freq
	};
	struct Message{
		MsgType type;
	};
	
	class Node
	{
	protected:
		static double rate;
		std::queue<char*> messages;
		std::vector<Node*> inputs;
		unsigned long size;
	public:
		Node(double Rate);
		~Node();
		
		float* buffer;
		
		virtual void update(double t, long frames);
		virtual void addMessage(char* Message);
		void addInput(Node* Input);
		virtual float* getBuffer();
		static void setRate(double Rate);
	};
}

#endif//MUZAK_NODE