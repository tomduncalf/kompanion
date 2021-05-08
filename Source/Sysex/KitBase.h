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
    class KitBase : public Sysex::Sysex
    {
    public:
        virtual ~KitBase() {};

        virtual void injectMidiControls() = 0;
        virtual void setTargetKit (int targetKit) = 0;

    protected:
        KitBase (juce::MemoryBlock message) : Sysex (message) {};
    };

} // namespace Sysex
} // namespace Kompanion
