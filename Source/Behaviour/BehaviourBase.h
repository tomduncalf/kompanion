/**
 Base class for a Behaviour. A Behaviour adds specific functionality to a Device, usually by
 adding listeners to it in the enable() method, and removing those listeners in disable().
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
}// namespace Behaviour
}// namespace Kompanion
