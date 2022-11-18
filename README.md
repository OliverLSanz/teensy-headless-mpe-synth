# Teensy Headless MPE Synth
This is a sound synthesizer for the [Teensy microcontroller](https://www.pjrc.com/teensy/).

The goal of this project is to build a small and portable MPE synth as a companion
for the [LinnStrument](https://www.rogerlinndesign.com/linnstrument) MIDI controller. This fulfils my need of being able to jump in a short practising session in the couch or in the park,
without carrying my computer with me.

## Features
- It implements the [MIDI Polyohonic Expression Specification](https://www.midi.org/midi-articles/midi-polyphonic-expression-mpe) (MPE for short).
- The synth is headless, meaning that there is no physical source of input like
buttons or knobs. The synth is entirelly controlled by MIDI.
-  Polyphony with a configurable number of voices.
- The MIDI is delivered by the synth by a USB port.
- The synth has USB-host capabilities. It can power MIDI controllers connected
to it.
- Jack 3.5 audio output.
- It can be powered by regular a USB powerbank for portability, so you only need the powerbank, the synth, a MIDI controller and your headphones :-)

# LinnStrument recommended settings
Configure your LinnStrument like this to get the most out of the synth:

- MIDI Mode: ChPerNote.
- PerNoteChs: All 16 channels.
- Bend Range: 24.
- Pitch/X: ON.
- Timbre/Y: ON.
- Loudness/Z: ON.

# Hardware

## Shopping list

If you want to build your own, you'll need:
- [Teensy 4.1](https://www.pjrc.com/store/teensy41.html). Will probably work with Teensy 4.0.
- [Teensy Audio Shield](https://www.pjrc.com/store/teensy3_audio.html).
- An USB type A female socket.
## Build

No schematics needed! Just
- Connect the audio shield to the Teensy (instructions on the [pjrc](https://www.pjrc.com) site).
- Connect the USB type A to the Teensy (check the Teensy pinout to see where it goes).

## Loading the software
This can be done using the Arduino IDE after installing some Teensy plug ins. There are plenty of tutorials out there.

# State of the project

This is not finished, but it is in a working state that fulfills my needs. I don't feel like continuing development since I have higher priority projects right now.

Collaborators and feedback are welcomed! I would love to hear your comments. If this is useful for other people I may feel the urge to continue working on this.

## Planned features
Not yet implemented and they probably won't be:
- Control Synth parameters via CC messages.
- Implement some sort of sound generation better than a simple waveform per voice like it is right now.
- Make sound respond to the Timbre/Y dimension.