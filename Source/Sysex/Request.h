/*
  ==============================================================================

    Request.h
    Created: 3 May 2021 4:13:39pm
    Author:  Tom Duncalf

  ==============================================================================
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
} // namespace Sysex
} // namespace Kompanion