#ifndef _MPESynth
#define _MPESynth

#include <Audio.h>
// #include "interfaces/Synth.h"
// #include "interfaces/Voice.h"

#include "SimpleVoice.h"

#ifndef ULLONG_MAX
#define ULLONG_MAX 0xffffffffffffffff
#endif

/*
 * Synth
 */
// class MPESynth: public Synth {
class MPESynth {

  private:
    SimpleVoice *voices;

    AudioMixer4 *mixers;

    byte voiceCount;
    byte mixerCount;
    byte audioConnectionCount;
    byte mixersCount;
    AudioMixer4 *output;

  public:
    MPESynth(SimpleVoice *voices, byte voiceCount);

    void noteOn(byte channel, byte note, byte velocity);
    void noteOff(byte channel, byte note, byte velocity);
    void controlChange(byte channel, byte control, byte value);
    void pitchChange(byte channel, int pitch);
    void afterTouch(byte channel, byte pressure);
    SimpleVoice *getVoices();
    AudioMixer4 * getOutput();

};

/**
 * Constructor
 */
inline MPESynth::MPESynth(SimpleVoice *voices, byte voiceCount){
  const byte voicesPerMixer = 4;
  this->voiceCount = voiceCount;
  this->mixerCount = this->voiceCount/voicesPerMixer + this->voiceCount%voicesPerMixer > 0? 1:0;
  this->audioConnectionCount = this->mixerCount + this->voiceCount;

  this->voices = voices;

  this->output = new AudioMixer4();
  this->output->gain(0, 1 );
  this->output->gain(1, 1 );
  this->output->gain(2, 1 );
  this->output->gain(3, 1 );

  this->mixers = new AudioMixer4[this->mixerCount];
  for (int i = 0; i < this->mixerCount; i++) {
    this->mixers[i].gain(0, 0.6 );
    this->mixers[i].gain(1, 0.6 );
    this->mixers[i].gain(2, 0.6 );
    this->mixers[i].gain(3, 0.6 );

    new AudioConnection(this->mixers[i], 0, *this->output, i%voicesPerMixer);
  }

  for (int i = 0; i < voiceCount; i++) {
    new AudioConnection(*this->voices[i].getOutput(), 0, this->mixers[i/voicesPerMixer], i%voicesPerMixer);
  }
}

/**
 * Note on
 */
inline void MPESynth::noteOn(byte channel, byte note, byte velocity){
  bool foundOne = false;
  int oldestVoice = 0;
  unsigned long oldestVoiceTime = ULLONG_MAX;

  for (int i = 0; i < voiceCount; i++) {
    // Search for the oldest voice
    if(this->voices[i].last_played < oldestVoiceTime){
      oldestVoiceTime = this->voices[i].last_played;
      oldestVoice = i;
    }

    // Search for an inactive voice
    if(!this->voices[i].isActive()){
      this->voices[i].noteOn(channel, note, velocity);
      foundOne = true;
      break;
    }
  }

  // No inactive voice then will take over the oldest note
  if(!foundOne){
    this->voices[oldestVoice].noteOn(channel, note, velocity);
  }
}

/**
 * Note off
 */
inline void MPESynth::noteOff(byte channel, byte note, byte velocity){
  for (int i = 0; i < voiceCount ; i++) {
    if(this->voices[i].currentNote == note){
      this->voices[i].noteOff(channel, note, velocity);
    }
  }
}

/**
 * Return the audio output
 */
inline AudioMixer4 * MPESynth::getOutput(){
  return this->output;
}

/**
 * Control Change
 */
void MPESynth::controlChange(byte channel, byte control, byte value){
  for (int i = 0; i < voiceCount ; i++) {
    if(this->voices[i].channel == channel && this->voices[i].isActive()){
      this->voices[i].controlChange(channel, control, value);
    }
  }
}


void MPESynth::pitchChange(byte channel, int pitch){
  for (int i = 0; i < voiceCount ; i++) {
    if(this->voices[i].channel == channel && this->voices[i].isActive()){
      this->voices[i].pitchChange(channel, pitch);
    }
  }
}

void MPESynth::afterTouch(byte channel, byte pressure){
  for (int i = 0; i < voiceCount ; i++) {
    if(this->voices[i].channel == channel && this->voices[i].isActive()){
      this->voices[i].afterTouch(channel, pressure);
    }
  }
}

inline SimpleVoice* MPESynth::getVoices(){
  return this->voices;
}

#endif
