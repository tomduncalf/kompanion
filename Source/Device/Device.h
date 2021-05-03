/*
  ==============================================================================

    Device.h
    Created: 2 May 2021 6:27:25pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Sysex/Digitone/Kit.h"
#include "../Sysex/KitBase.h"

namespace Kompanion
{
namespace Device
{
    using PatternChangeCallback = std::function<bool (int, int)>;
    using KitCallback = std::function<bool (Kompanion::Sysex::KitBase&)>;

    class Device : public juce::MidiInputCallback
    {
    protected:
        Device (juce::String defaultMidiDeviceName, uint8_t deviceSysexId);

        std::unique_ptr<juce::MidiInput> midiInput;
        std::unique_ptr<juce::MidiOutput> midiOutput;

        std::vector<PatternChangeCallback> patternChangeCallbacks;
        std::vector<KitCallback> kitCallbacks;

        juce::String defaultMidiDeviceName;
        uint8_t deviceSysexId;

        int currentPattern = 0;

        void initialiseDefaultMidiDevices();

        void requestKit (int index);

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
