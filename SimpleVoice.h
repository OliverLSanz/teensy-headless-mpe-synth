#ifndef _SimpleVoice
#define _SimpleVoice

#include <Audio.h>
#include "interfaces/Voice.h"

/*
 * SimpleVoice
 */
class SimpleVoice: public Voice {
  private:
    AudioSynthWaveform       *waveGenerator;
    AudioMixer4              *output;
    AudioConnection          *patchCord1;
    AudioConnection          *patchCord2;

    bool notePlayed;

  public:
    SimpleVoice();

    byte currentNote;
    byte channel;  // for MPE
    unsigned long last_played;

    AudioMixer4 * getOutput();
    void noteOn(byte channel, byte note, byte velocity);
    void noteOff(byte channel, byte note, byte velocity);
    void controlChange(byte channel, byte control, byte value);
    void pitchChange(byte channel, int pitch);
    void afterTouch(byte channel, byte pressure);
    bool isActive();
};

/**
 * Constructor
 */
inline SimpleVoice::SimpleVoice(){
  this->waveGenerator = new AudioSynthWaveform();
  this->waveGenerator->begin(WAVEFORM_SAWTOOTH_REVERSE);
  this->waveGenerator->amplitude(1);

  this->output = new AudioMixer4();
  this->output->gain(0, 0.6);

  this->patchCord1 = new AudioConnection(*this->waveGenerator, 0, *this->output, 0);
  this->patchCord2 = new AudioConnection(*this->waveGenerator, 0, *this->output, 1);

  this->notePlayed = false;
}

/**
 * Return the audio output
 */
inline AudioMixer4 * SimpleVoice::getOutput(){
  return this->output;
}

/**
 * Note on
 */
inline void SimpleVoice::noteOn(byte channel, byte note, byte velocity) {
  float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);
  this->waveGenerator->frequency(freq);
  this->waveGenerator->amplitude(float(map(velocity, 0, 127, 0, 100))/100);
  this->last_played = millis();
  this->notePlayed=true;
  this->currentNote = note;
  this->channel = channel;
}

/**
 * Note off
 */
inline void SimpleVoice::noteOff(byte channel, byte note, byte velocity) {
  this->waveGenerator->amplitude(0);
  this->notePlayed=false;
}

/**
 * Control change
 */
inline void SimpleVoice::controlChange(byte channel, byte control, byte value) {
}

/**
 * Pitch change
 */
inline void SimpleVoice::pitchChange(byte channel, int pitch){
  float offset = float(pitch) / 342;  // 342 corresponding to pitch range 24
  float freq = 440.0 * powf(2.0, (float(this->currentNote) - 69 + offset) * 0.08333333);
  this->waveGenerator->frequency(freq);
}

/**
 * Pitch change
 */
inline void SimpleVoice::afterTouch(byte channel, byte pressure){
  this->waveGenerator->amplitude(float(map(pressure, 0, 127, 0, 100))/100);
}

/**
 * Is the voice active
 */
inline bool SimpleVoice::isActive(){
  return this->notePlayed;
}

#endif