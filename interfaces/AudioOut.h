#ifndef _interfaces_AudioOut
#define _interfaces_AudioOut

#include <Audio.h>

class AudioOut {
  public:
    virtual AudioMixer4 * getOutput();
};

#endif