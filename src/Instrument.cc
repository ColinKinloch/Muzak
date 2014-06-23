// Copyright © 2014 Colin Kinloch <colinmkinloch@gmail.com> - All Rights Reserved
// Licence in LICENSE

#include <Muzak/Instrument.hh>
#include <stdio.h>

Muzak::Instrument::Instrument(): Muzak::Instrument::Instrument(Muzak::Wave::TRIANGLE)
{}
Muzak::Instrument::Instrument(Wave Type): Muzak::Instrument::Instrument(Muzak::Wave::TRIANGLE, 44100.f)
{}
Muzak::Instrument::Instrument(Wave Type, double Rate): Muzak::Node::Node(Rate)
{
  currSize = 0;
  currBuff = new float[currSize]();
  type = Type;
  gen = Muzak::Generator(Type, Rate);
}
Muzak::Instrument::~Instrument()
{
  delete currBuff;
}

void Muzak::Instrument::tune(double Freq)
{
  tuning = Freq;
}

void Muzak::Instrument::update(double t, long frames)
{
  Muzak::Node::update(t, frames);
  if(currSize<frames)
  {
    delete currBuff;
    currSize = frames;
    currBuff = new float[currSize];
  }
  for(int i=0; i<frames; i++)
   currBuff[i] = 0.f;

  auto it = inputs.begin();
  auto end = inputs.end();
  for(;it!=end;it++)
  {
    std::map<unsigned char, unsigned char> notes = static_cast<Muzak::Midi*>(*it)->notes;
    auto nit = notes.begin();
    auto nend = notes.end();
    for(;nit!=nend;nit++)
    {
      float amp = nit->second/(float)127;
      float* noteBuff = gen.makeFloat(midiToFreq(nit->first), t, frames);
      for(int i=0;frames>i;i++)
       currBuff[i] += noteBuff[i]*amp;
    }
  }

  for(int i=0;frames>i;i++)
   buffer[i] = currBuff[i];
}

float Muzak::Instrument::midiToFreq(unsigned char note)
{
  signed char n = note-0x48;
  return pow(2, (n/(float)12))*tuning;
}
