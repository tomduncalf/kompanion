/*
  ==============================================================================

    Kit.h
    Created: 2 May 2021 6:13:08pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#pragma once

#include "Sysex.h"

namespace Kompanion
{
namespace Sysex
{
    class KitBase : public Kompanion::Sysex::Sysex
    {
    public:
        virtual ~KitBase() {};

    protected:
        KitBase (juce::MemoryBlock message) : Sysex (message) {};

        virtual void injectMidiControls() = 0;
        virtual void setTargetKit (int targetKit) = 0;
    };

} // namespace Sysex
} // namespace Kompanion
