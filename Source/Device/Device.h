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
    using PatternChangeCallback = std::function<bool (int, int)>;

    class Device : public juce::MidiInputCallback
    {
    protected:
        Device (juce::String defaultMidiDeviceName);

        std::unique_ptr<juce::MidiInput> midiInput;
        std::unique_ptr<juce::MidiOutput> midiOutput;

        std::vector<PatternChangeCallback> patternChangeCallbacks;

        juce::String defaultMidiDeviceName;

        int currentPattern = 0;

        void initialiseDefaultMidiDevices();

        void handleIncomingMidiMessage (juce::MidiInput* source, const juce::MidiMessage& message);

        template <typename T, typename... Targs>
        void callCallbacks (std::vector<T>& callbacks, Targs... Fargs)
        {
            for (auto callback = callbacks.begin(); callback < callbacks.end(); ++callback)
            {
                auto removeCallback = (*callback) (Fargs...);

                if (removeCallback)
                    callback = callbacks.erase (callback);
            }
        }
    };

} // namespace Device
} // namespace Kompanion
