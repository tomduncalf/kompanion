/**
 KitLockBehaviour implements a Behaviour which keeps the current kit
 of sounds locked as the user changes patterns, to emulate the Kit functionality
 found on larger Elektron devices. It does this by listening for pattern
 change messages, and when the user changes pattern, it grabs the
 preivous pattern's kit and sends it to the current pattern.
 */
#pragma once

#include "BehaviourBase.h"

namespace Kompanion
{
namespace Behaviour
{
    class KitLockBehaviour : public BehaviourBase
    {
    public:
        KitLockBehaviour (Device::Device& device);

        void enable() override;
        void disable() override;
    };
}// namespace Behaviour
}// namespace Kompanion
