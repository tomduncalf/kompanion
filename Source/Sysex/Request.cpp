/*
  ==============================================================================

    Request.cpp
    Created: 3 May 2021 4:13:39pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#include "Request.h"

namespace Kompanion
{
namespace Sysex
{
    Request::Request (uint8_t deviceSysexId, uint8_t type, uint8_t index) : deviceSysexId (deviceSysexId),
                                                                            type (type),
                                                                            index (index)
    {
    }

    juce::MidiMessage Request::getMessage()
    {
        uint8_t request[13] = { 0x00, 0x20, 0x3c, deviceSysexId, 0x00, type, 0x01, 0x01, index, 0x00, 0x00, 0x00, 0x05 };

        return juce::MidiMessage::createSysExMessage (request, 13);
    }
} // namespace Sysex
} // namespace Kompanion