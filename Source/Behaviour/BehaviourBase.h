/*
  ==============================================================================

    BehaviourBase.h
    Created: 8 May 2021 3:53:28pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Device/Device.h"

namespace Kompanion
{
namespace Behaviour
{
    class BehaviourBase
    {
    public:
        virtual ~BehaviourBase() {};

        virtual void enable() = 0;
        virtual void disable() = 0;

    protected:
        BehaviourBase (Device::Device& device);

        Device::Device& device;
    };
} // namespace Behaviour
} // namespace Kompanion