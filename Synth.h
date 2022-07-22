#ifndef Synth_h
#define Synth_h

#include <Audio.h>
#include "Voice.h"

#ifndef ULLONG_MAX
#define ULLONG_MAX 0xffffffffffffffff
#endif

// Number of voices
const byte voiceCount = 4; // max = 16
const byte voicesPerMixer = 4;
const byte mixerCount = voiceCount/voicesPerMixer + voiceCount%voicesPerMixer > 0? 1:0;

/*
 * Synth
 */
class Synth{
  
  private:
    Voice *voices[voiceCount];
    
    AudioConnection* patchCords[mixerCount + voiceCount]; 
    AudioMixer4 *mixers[mixerCount];
    AudioMixer4 *output;
    
  public:
    Synth();

    void noteOn(byte channel, byte note, byte velocity);
    void noteOff(byte channel, byte note, byte velocity);
    void controlChange(byte channel, byte control, byte value);
    Voice **getVoices();
    AudioMixer4 * getOutput();

};

/**
 * Constructor
 */
inline Synth::Synth(){
  this->output = new AudioMixer4();
  this->output->gain(0, 1 );
  this->output->gain(1, 1 );
  this->output->gain(2, 1 );
  this->output->gain(3, 1 );

  for (int i = 0; i < mixerCount; i++) {
    this->mixers[i] = new AudioMixer4();
    this->mixers[i]->gain(0, 0.6 );
    this->mixers[i]->gain(1, 0.6 );
    this->mixers[i]->gain(2, 0.6 );
    this->mixers[i]->gain(3, 0.6 );
    
    this->patchCords[i] = new AudioConnection(*this->mixers[i], 0, *this->output, i%voicesPerMixer);
  }
  
  for (int i = 0; i < voiceCount; i++) {
    this->voices[i] = new Voice();
    this->patchCords[i] = new AudioConnection(*this->voices[i]->getOutput(), 0, *this->mixers[i/voicesPerMixer], i%voicesPerMixer);
  }
}

/**
 * Note on
 */
inline void Synth::noteOn(byte channel, byte note, byte velocity){
  bool foundOne = false;
  int oldestVoice = 0;
  unsigned long oldestVoiceTime = ULLONG_MAX;

  for (int i = 0; i < voiceCount; i++) {
    // Search for the oldest voice
    if(this->voices[i]->last_played < oldestVoiceTime){
      oldestVoiceTime = this->voices[i]->last_played;
      oldestVoice = i;
    }
    
    // Search for an inactive voice
    if(!this->voices[i]->isActive()){
      this->voices[i]->noteOn(channel, note, velocity);
      foundOne = true;
      break;
    }
  }

  // No inactive voice then will take over the oldest note
  if(!foundOne){
    this->voices[oldestVoice]->noteOn(channel, note, velocity);
  }
}

/**
 * Note off
 */
inline void Synth::noteOff(byte channel, byte note, byte velocity){
  for (int i = 0; i < voiceCount ; i++) {
    if(this->voices[i]->currentNote == note){
      this->voices[i]->noteOff(channel, note, velocity);
    }
  }
}

/**
 * Return the audio output
 */
inline AudioMixer4 * Synth::getOutput(){
  return this->output;
}

/**
 * Control Change
 */
void Synth::controlChange(byte channel, byte control, byte ccValue){

}

inline Voice** Synth::getVoices(){
  return this->voices;
}

#endif
