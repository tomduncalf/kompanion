# Kompanion

Kompanion is a project designed to add additional functionality to Elektron music hardware, by running an app on a computer or mobile device connected via USB/MIDI to the hardware, which can use MIDI messages to perform various "tricks" which expand the hardware's functionality.

Example functionality planned:

- Implement "kit" functionality for Digitone/Digitakt devices, allowing you to share the same set of sounds across multiple patterns (as it works on e.g. the Analog Four/Rytm).

  This is implemented by listening for pattern change messages, and when one is receieved, the app requests the previous pattern's kit and sends it to the current pattern (using unpublished SysEx commands, thanks to [libanalogrytm](https://github.com/bsp2/libanalogrytm) for these). This happens instantly, so it feels as if the same kit is shared between patterns (i.e. any changes you make as you are playing pattern 1 will sync to pattern 2).

  **Status:** [Working version implemented](https://github.com/tomduncalf/kompanion/blob/main/Source/Behaviour/KitLockBehaviour.cpp), needs UI to enable/disable "kit lock" (right now it is always on).

- Implement macro/performance controls (as seen on Analog Rytm/Four) for Digitone/Digitakt devices, using the CC controls on one of the MIDI tracks as the macro knobs and then listening for these messages and sending out parameter change messages.

  **Status:** [Code](https://github.com/tomduncalf/kompanion/blob/main/Source/Sysex/Digitone/Kit.cpp#L11) to inject MIDI CC control knobs into any kit written. I have an earlier prototoype of macro control working the same way, which works well, but it needs rewriting.

- Implement "Ctrl-All" functionality for devices which do not support it (where changing a parameter on one track affects every track).

  **Status:** not started.

## Status

Work in progress – basic kit lock functionality is implemented and working on Digitone, but there is no user interface. The plan is to use my [juce_browser_integration](https://github.com/tomduncalf/juce_browser_integration) module to build the UI once that is complete.

## Technical notes

The app is written in C++ using JUCE, to allow it to work cross-platform.

The concept is that each bit of extra functionality can be written as a [Behaviour](https://github.com/tomduncalf/kompanion/tree/main/Source/Behaviour). A Behaviour gets a reference to the [Device](https://github.com/tomduncalf/kompanion/blob/main/Source/Device/Device.h), and so can add functionality by adding listeners to and calling methods on the Device instance.

Users will be able to select which Behaviours are active in the UI.

## TODO

- [ ] Add additional behaviours
- [ ] Support other Elektron devices
- [ ] UI
- [ ] Code review/cleanup
