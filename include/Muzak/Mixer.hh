// Copyright © 2014 Colin Kinloch <colinmkinloch@gmail.com> - All Rights Reserved
// Licence in LICENSE

#ifndef MUZAK_MIXER
#define MUZAK_MIXER

#include <Muzak/Node.hh>

namespace Muzak
{
  class Mixer: public Node
  {
  private:
    float* tempBuff;
    unsigned long tempSize;
  public:
    Mixer();
    Mixer(double Rate);
    ~Mixer();

    void update(double t, long frames);
  };
}

#endif//MUZAK_MIXER
