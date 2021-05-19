/**
 Represents a Digitone kit
 */

#pragma once

#include "../KitBase.h"

namespace Kompanion
{
namespace Sysex
{
    namespace Digitone
    {
        class Kit : public KitBase
        {
        public:
            Kit (juce::MemoryBlock message): KitBase (message) {};

            void injectMidiControls() override;
            void setTargetKit (int targetKit) override;
        };

    }// namespace Digitone
}// namespace Sysex
}// namespace Kompanion
