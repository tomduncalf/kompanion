/**
 Base class representing a Kit Sysex message. Each device
 may have its own specialisation of this class.
 */
#pragma once

#include "Sysex.h"

namespace Kompanion
{
namespace Sysex
{
    class KitBase : public Sysex::Sysex
    {
    public:
        virtual ~KitBase() {};

        virtual void injectMidiControls() = 0;
        virtual void setTargetKit (int targetKit) = 0;

    protected:
        KitBase (juce::MemoryBlock message): Sysex (message) {};
    };

}// namespace Sysex
}// namespace Kompanion
