[Demo](https://github.com/OliverLSanz/teensy-headless-mpe-synth/edit/master/README.md#prototype-demo)
 / [Features](https://github.com/OliverLSanz/teensy-headless-mpe-synth/edit/master/README.md#features)
 / [LinnStrument settings](https://github.com/OliverLSanz/teensy-headless-mpe-synth/edit/master/README.md#linnstrument-recommended-settings)
 / [Hardware](https://github.com/OliverLSanz/teensy-headless-mpe-synth/edit/master/README.md#hardware)
 / [Software](https://github.com/OliverLSanz/teensy-headless-mpe-synth/edit/master/README.md#software)
 / [State of the project](https://github.com/OliverLSanz/teensy-headless-mpe-synth/edit/master/README.md#state-of-the-project)

# Teensy Headless MPE Synth
This is a sound synthesizer for the [Teensy microcontroller](https://www.pjrc.com/teensy/).

The goal of this project is to build a small and portable MPE synth as a companion
for the [LinnStrument](https://www.rogerlinndesign.com/linnstrument) MIDI controller. This fulfils my need of being able to jump in a short practising session while comfortably reclining in the couch or breathing fresh air in the park, leaving my computer with at home.

## Prototype demo!
This prototype is built with development convenience in mind. The components could easily fit in 1/3 the volume for maximum portability.

Synth in wooden box!

<img src="https://user-images.githubusercontent.com/15345234/202673000-d4c6898d-8394-442b-b7b8-877eb3dc9f1f.jpeg" width="300" />
<img src="https://user-images.githubusercontent.com/15345234/202673004-a9377808-c1d2-4e1f-88bc-9e5d4c7590b9.jpeg" width="300" />
<img src="https://user-images.githubusercontent.com/15345234/202673039-6efc1301-1a9b-45c9-ba45-263457ce5d23.jpeg" width="300" />
Full LinnStrument setup powered by power bank:

<img src="https://user-images.githubusercontent.com/15345234/202673415-b3fc2b53-796a-4d89-87e6-f39cc2d4f727.jpeg" width="300" />


### Demo song (turn up video player volume)
https://user-images.githubusercontent.com/15345234/202672777-879ea173-8e16-452c-9b17-6823afa3fe5b.mp4

### Slide and loudnes
https://user-images.githubusercontent.com/15345234/202672802-54e3bbb5-0b7d-4149-a507-6c5db28aa252.mp4

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

# Software
The project is divided into 3 files:
- `mpe-synth.ino`: Arduino sketch file, defining the `loop` and `setup` functions. Here the synth is configured and the incoming MIDI messages are passed to the actual synth. If you want to modify the info sent to the synth, edit here.
- `Synth.h`: contains the synth code, that handles MIDI messages and forwards them to the corresponding voice. If you want to change the behavior of the synth, edit here.
- `Voice.h`: Here is the code that produces sound for each of the voices. For now, just a simple waveform. If you want to change how the synth sounds, edit here.

# State of the project

This is not finished, but it is in a working state that fulfills my needs. I don't feel like continuing development since I have higher priority projects right now.

Collaborators and feedback are welcomed! I would love to hear your comments. If this is useful for other people I may feel the urge to continue working on this.

## Planned features
Not yet implemented and they probably won't be:
- Control Synth parameters via CC messages.
- Implement some sort of sound generation better than a simple waveform per voice like it is right now.
- Make sound respond to the Timbre/Y dimension.

# Thanks
Thank to ghostintranslation for its [SimpleSynth](https://github.com/ghostintranslation/SimpleSynth) code which has greatly inspired this!

And of course thanks to Roger Linn for designing this amazing interface :-)
