#ifndef _interfaces_Voice
#define _interfaces_Voice

#include <Audio.h>
#include "MidiHandler.h"
#include "AudioOut.h"

class patata {};

class Voice: public MidiHandler, public AudioOut {
  public:
    byte currentNote;
    byte channel;  // Corresponding MPE channel
    unsigned long last_played;
    virtual bool isActive();
};

#endif