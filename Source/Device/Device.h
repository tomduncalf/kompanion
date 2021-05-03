/*
  ==============================================================================

    Device.h
    Created: 2 May 2021 6:27:25pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace Kompanion
{
namespace Device
{
    class Device : public juce::MidiInputCallback
    {
    protected:
        Device (juce::String defaultMidiDeviceName);

        std::unique_ptr<juce::MidiInput> midiInput;
        std::unique_ptr<juce::MidiOutput> midiOutput;

        juce::String defaultMidiDeviceName;

        void initialiseDefaultMidiDevices();

        void handleIncomingMidiMessage (juce::MidiInput* source, const juce::MidiMessage& message)
        {
            DBG (message.getDescription());
        }
    };

} // namespace Device
} // namespace Kompanion
