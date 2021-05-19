/**
 Request represents a Sysex request to an Elektron device.
 These requests all follow a common structure, with a few bytes
 changing based on the device and feature we are using.
 */

#pragma once

#include "JuceHeader.h"

namespace Kompanion
{
namespace Sysex
{
    class Request
    {
    public:
        Request (uint8_t deviceSysexId, uint8_t type, uint8_t index);

        juce::MidiMessage getMessage();

    protected:
        uint8_t deviceSysexId;
        uint8_t type;
        uint8_t index;
    };
}// namespace Sysex
}// namespace Kompanion
