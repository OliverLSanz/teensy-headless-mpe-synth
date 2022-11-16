#ifndef _interfaces_MidiHandler
#define _interfaces_MidiHandler

class MidiHandler {
  public:
    virtual void noteOn(byte channel, byte note, byte velocity);
    virtual void noteOff(byte channel, byte note, byte velocity);
    virtual void controlChange(byte channel, byte control, byte value);
    virtual void pitchChange(byte channel, int pitch);
    virtual void afterTouch(byte channel, byte pressure);
};

#endif