/*
  ==============================================================================

    DigiBase.h
    Created: 2 May 2021 6:26:58pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#pragma once

#include "Device.h"

namespace Kompanion
{
namespace Device
{
    class DigiBase : public Device
    {
    protected:
        DigiBase (juce::String defaultMidiDeviceName,
                  uint8_t deviceSysexId) : Device (defaultMidiDeviceName,
                                                   deviceSysexId) {};
    };

} // namespace Device
} // namespace Kompanion
