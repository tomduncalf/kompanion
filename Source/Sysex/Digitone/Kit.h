/*
  ==============================================================================

    Kit.h
    Created: 2 May 2021 6:13:08pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#pragma once

#include "../Sysex.h"

namespace Kompanion
{
namespace Sysex
{
    namespace Digitone
    {
        class Kit : public Kompanion::Sysex::Sysex
        {
        public:
            Kit (juce::MemoryBlock message) : Sysex (message) {};

            void injectMidiControls();
            void setTargetKit (int targetKit);
        };

    } // namespace Digitone
} // namespace Sysex
} // namespace Kompanion
