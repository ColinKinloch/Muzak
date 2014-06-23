// Copyright © 2014 Colin Kinloch <colinmkinloch@gmail.com> - All Rights Reserved
// Licence in LICENSE

#ifndef MUZAK_GENERATOR
#define MUZAK_GENERATOR

#include <Muzak/Node.hh>
#include <Muzak/gens/Sine.hh>
#include <random>
#include <cmath>
//chrono?
#include <ctime>

namespace Muzak
{
  enum class Wave{TRIANGLE, SAWTOOTH, SQUARE, NOISE, DIRTY, SINE, HALFSINE, MODSINE, SINETOOTH};

  class Generator
  {
  private:
    std::default_random_engine rng;
    std::uniform_real_distribution<float> uniform = std::uniform_real_distribution<float>(-1.0f, 1.0f);
    unsigned long size;
    float* buffer;
    double rate;
    int m;
    gens::Sine sine;
  public:
    Generator();
    Generator(Wave Type);
    Generator(Wave Type, double Rate);
    ~Generator();

    Wave type;

    float* makeFloat(float freq, double t, unsigned long frames);
  };
}

#endif//MUZAK_GENERATOR
