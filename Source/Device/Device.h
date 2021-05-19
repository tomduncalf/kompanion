/**
 Base class for a Device. A Device represents a piece of Elektron hardware,
 and is the main class we interact with for listening to and sending messages.
 Each specific device implements its own subclass of Device with some
 specific config information.
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
    using KitCallback = std::function<bool (std::unique_ptr<Sysex::KitBase>)>;

    class Device : public juce::MidiInputCallback
    {
    public:
        void addPatternChangeCallback (PatternChangeCallback callback);
        void addKitCallback (KitCallback callback);

        void requestKit (int index);

        void sendMessage (const juce::MidiMessage& message);

    protected:
        Device (juce::String defaultMidiDeviceName, uint8_t deviceSysexId);

        std::unique_ptr<juce::MidiInput> midiInput;
        std::unique_ptr<juce::MidiOutput> midiOutput;

        template<typename T>
        void addCallback (T callback, std::vector<T>& callbackList)
        {
            callbackList.push_back (callback);
        }

        std::vector<PatternChangeCallback> patternChangeCallbacks;
        std::vector<KitCallback> kitCallbacks;

        juce::String defaultMidiDeviceName;
        uint8_t deviceSysexId;

        int currentPattern = 0;

        void initialiseDefaultMidiDevices();

        virtual std::unique_ptr<Sysex::KitBase> createKit (juce::MemoryBlock message) = 0;

        void handleIncomingMidiMessage (juce::MidiInput* source, const juce::MidiMessage& message);

        template<typename T, typename... Args>
        void callCallbacks (std::vector<T>& callbacks, Args... args)
        {
            for (auto callback = callbacks.begin(); callback < callbacks.end(); ++callback)
            {
                auto removeCallback = (*callback) (std::forward<Args&&> (args)...);

                if (removeCallback)
                    callback = callbacks.erase (callback);
            }
        }
    };

}// namespace Device
}// namespace Kompanion
