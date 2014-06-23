// Copyright © 2014 Colin Kinloch <colinmkinloch@gmail.com> - All Rights Reserved
// Licence in LICENSE

#include <Muzak/Mixer.hh>
#include <cstdio>

Muzak::Mixer::Mixer(): Muzak::Mixer::Mixer(0.f)
{}
Muzak::Mixer::Mixer(double Rate): Muzak::Node::Node(Rate)
{
  tempSize = 0;
  tempBuff = new float[tempSize]();
}
Muzak::Mixer::~Mixer()
{
  delete tempBuff;
}

void Muzak::Mixer::update(double t, long frames)
{
  Muzak::Node::update(t, frames);
  if(tempSize<frames)
  {
    delete tempBuff;
    tempSize = frames;
    tempBuff = new float[tempSize];
  }
  for(int i=0; i<frames; i++)
   tempBuff[i] = 0.f;

  auto it = inputs.begin();
  auto end = inputs.end();
  for(;it!=end;it++)
  {
    (*it)->update(t, frames);
    float* inbuff = (*it)->getBuffer();

    for(int i=0;frames>i;i++)
     tempBuff[i] += inbuff[i];
  }

  for(int i=0;frames>i;i++)
   buffer[i] = tempBuff[i];
}
