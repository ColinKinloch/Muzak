// Copyright © 2014 Colin Kinloch <colinmkinloch@gmail.com> - All Rights Reserved
// Licence in LICENSE

#include <Muzak/Midi.hh>
#include <cstdio>

Muzak::Midi::Midi(): Muzak::Node::Node(0.f)
{}
Muzak::Midi::~Midi()
{}

void Muzak::Midi::update()
{
  Muzak::Node::update(0, 0);
  unsigned long msg;
  unsigned char msg1, msg2, msg3;
  while(!messages.empty())
  {
    msg = (long)messages.front();
    msg1 = msg&0x0000ff;
    msg2 = (msg&0x00ff00)/0x100;
    msg3 = (msg&0xff0000)/0x10000;
    switch(msg1)
    {
      case 0x90:
      {
        if(msg3==0x00)
        {
          notes.erase(msg2);
          printf("%hhX: off\n", msg2);
        }
        else
        {
          notes.insert(std::pair<unsigned char, unsigned char>(msg2, msg3));
          printf("%hhX: on at %hhu\n", msg2, msg3);
        }
        break;
      }
      case 0x80:
      {
        printf("%hhX: off\n", msg2);
        break;
      }
      case 0xe0:
      {
        printf("pitch at %hhu\n", msg3);
        break;
      }
      case 0xb0:
      {
        printf("mod %hhu at %hhu\n", msg2, msg3);
        break;
      }
    }
    messages.pop();
  }
}
void Muzak::Midi::addMessage(MidiMsg msg)
{
  Muzak::Node::addMessage((char*)msg);
}
