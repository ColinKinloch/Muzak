// Copyright © 2014 Colin Kinloch <colinmkinloch@gmail.com> - All Rights Reserved
// Licence in LICENSE

#include <Muzak/Node.hh>
#include <stdio.h>

double Muzak::Node::rate = 44100.f;

Muzak::Node::Node(double Rate)
{
  rate = Rate;
  size = 0;
  buffer = new float[size]();
}
Muzak::Node::~Node()
{
  delete buffer;
}

void Muzak::Node::update(double t, long frames)
{
  if(size<frames)
  {
    delete buffer;
    size = frames;
    buffer = new float[size];
  }
}

void Muzak::Node::addInput(Muzak::Node* Input)
{
  inputs.push_back(Input);
}
void Muzak::Node::addMessage(char* Message)
{
  messages.push(Message);
}

float* Muzak::Node::getBuffer()
{
  return buffer;
}

void Muzak::Node::setRate(double Rate)
{
  rate = Rate;
}
