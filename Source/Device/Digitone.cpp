#include "Digitone.h"

namespace Kompanion
{
namespace Device
{
    std::unique_ptr<Sysex::KitBase> Digitone::createKit (juce::MemoryBlock message)
    {
        return std::make_unique<Sysex::Digitone::Kit> (message);
    }
}// namespace Device
}// namespace Kompanion
