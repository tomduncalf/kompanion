/*
  ==============================================================================

    KitLockBehaviour.h
    Created: 8 May 2021 3:53:47pm
    Author:  Tom Duncalf

  ==============================================================================
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
} // namespace Behaviour
} // namespace Kompanion