/**
 Base class for Digitone/Digitakt devices
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
                  uint8_t deviceSysexId): Device (defaultMidiDeviceName,
                                                  deviceSysexId) {};
    };

}// namespace Device
}// namespace Kompanion
