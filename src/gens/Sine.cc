// Copyright © 2014 Colin Kinloch <colinmkinloch@gmail.com> - All Rights Reserved
// Licence in LICENSE

#include <Muzak/gens/Sine.hh>
#include <iostream>

//TODO circular buffing
Muzak::gens::Sine::Sine(unsigned int Length)
{
  size = Length;
  buffer = new float[Length];

  for( int i=0; i<Length; i++ )
  {
    double lt = i/(double)Length; //i*dt+t;
    buffer[i] = sin(2*M_PI*lt);
  }
}
Muzak::gens::Sine::~Sine()
{
  delete buffer;
}

float* Muzak::gens::Sine::makeFloat()
{
  return buffer;
}
