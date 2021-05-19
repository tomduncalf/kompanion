/**
 Represents a SysEx message
 */

#pragma once

#include <JuceHeader.h>

namespace Kompanion
{
namespace Sysex
{
    class Sysex
    {
    public:
        Sysex (juce::MemoryBlock message);

        juce::MidiMessage getMessage();

    protected:
        juce::MemoryBlock message;

    private:
        void injectChecksum();
    };

}// namespace Sysex
}// namespace Kompanion
