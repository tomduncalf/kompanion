/*
  ==============================================================================

    Digitone.h
    Created: 2 May 2021 6:27:03pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#pragma once

#include "DigiBase.h"

#include "../Sysex/Digitone/Kit.h"

namespace Kompanion
{
namespace Device
{
    class Digitone : public DigiBase
    {
    public:
        Digitone() : DigiBase ("Elektron Digitone", 0x0D) {};

    protected:
        std::unique_ptr<Sysex::KitBase> createKit (juce::MemoryBlock message) override;
    };

} // namespace Device
} // namespace Kompanion
