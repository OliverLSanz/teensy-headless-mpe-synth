#ifndef _interfaces_Synth
#define _interfaces_Synth

#include <Audio.h>
#include "AudioOut.h"
#include "MidiHandler.h"
#include "Voice.h"

class Synth: public MidiHandler, public AudioOut {
  public:
    Synth();
    Synth(Voice voices[]);
};

Synth::Synth(){};

#endif