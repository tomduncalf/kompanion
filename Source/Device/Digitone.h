/*
  ==============================================================================

    Digitone.h
    Created: 2 May 2021 6:27:03pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#pragma once

#include "DigiBase.h"

namespace Kompanion
{
namespace Device
{
    class Digitone : public DigiBase
    {
    public:
        Digitone() : DigiBase ("Elektron Digitone") {};
    };

} // namespace Device
} // namespace Kompanion
