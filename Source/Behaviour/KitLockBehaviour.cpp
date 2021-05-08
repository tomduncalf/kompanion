/*
  ==============================================================================

    KitLockBehaviour.cpp
    Created: 8 May 2021 3:53:47pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#include "KitLockBehaviour.h"

namespace Kompanion
{
namespace Behaviour
{
    KitLockBehaviour::KitLockBehaviour (Device::Device& device) : BehaviourBase (device)
    {
    }

    void KitLockBehaviour::enable()
    {
        device.addPatternChangeCallback ([this] (int lastPattern, int currentPattern)
                                         {
                                             device.addKitCallback ([this, currentPattern] (std::unique_ptr<Sysex::KitBase> kit)
                                                                    {
                                                                        kit->setTargetKit (currentPattern);
                                                                        device.sendMessage (kit->getMessage());
                                                                        return true;
                                                                    });

                                             device.requestKit (lastPattern);

                                             return false;
                                         });
    }

    void KitLockBehaviour::disable()
    {
    }
} // namespace Behaviour
} // namespace Kompanion