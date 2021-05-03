/*
  ==============================================================================

    Device.cpp
    Created: 2 May 2021 6:27:25pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#include "Device.h"

namespace Kompanion
{
namespace Device
{
    Device::Device (juce::String defaultMidiDeviceName) : defaultMidiDeviceName (defaultMidiDeviceName)
    {
        initialiseDefaultMidiDevices();

        patternChangeCallbacks.emplace_back ([this] (int lastPattern, int currentPattern)
                                             {
                                                 DBG (lastPattern << " to " << currentPattern);
                                                 return true;
                                             });
    }

    void Device::initialiseDefaultMidiDevices()
    {
        juce::MidiDeviceInfo inputInfo;

        for (auto& info : juce::MidiInput::getAvailableDevices())
        {
            if (info.name == defaultMidiDeviceName)
                inputInfo = info;
        }
        jassert (inputInfo.identifier != "");

        midiInput = juce::MidiInput::openDevice (inputInfo.identifier, this);
        jassert (midiInput != nullptr);

        juce::MidiDeviceInfo outputInfo;

        for (auto& info : juce::MidiOutput::getAvailableDevices())
        {
            if (info.name == defaultMidiDeviceName)
                outputInfo = info;
        }
        jassert (outputInfo.identifier != "");

        midiOutput = juce::MidiOutput::openDevice (outputInfo.identifier);
        jassert (midiOutput != nullptr);

        midiInput->start();
    }

    void Device::handleIncomingMidiMessage (juce::MidiInput* source, const juce::MidiMessage& message)
    {
        DBG (message.getDescription());

        if (message.isProgramChange())
        {
            auto lastPattern = currentPattern;
            currentPattern = message.getProgramChangeNumber();
            callCallbacks (patternChangeCallbacks, lastPattern, currentPattern);
        }
    }

} // namespace Device
} // namespace Kompanion
