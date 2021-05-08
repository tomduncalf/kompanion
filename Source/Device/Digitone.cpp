/*
  ==============================================================================

    Digitone.cpp
    Created: 2 May 2021 6:27:03pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#include "Digitone.h"

namespace Kompanion
{
namespace Device
{
    std::unique_ptr<Kompanion::Sysex::KitBase> Digitone::createKit (juce::MemoryBlock message)
    {
        return std::make_unique<Kompanion::Sysex::Digitone::Kit> (message);
    }
} // namespace Device
} // namespace Kompanion
