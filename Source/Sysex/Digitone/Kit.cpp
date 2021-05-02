/*
  ==============================================================================

    Kit.cpp
    Created: 2 May 2021 6:13:08pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#include "Kit.h"

namespace Kompanion { namespace Sysex { namespace Digitone {

void Kit::injectMidiControls()
{
    // This sets MIDI T4 to output CC on channel 1
    int start = 2321;
    message.setBitRange (start * 8, 8, 0x20);
    message.setBitRange ((start + 1) * 8, 8, 0x00);
    message.setBitRange ((start + 2) * 8, 8, 0x7f);
    message.setBitRange ((start + 3) * 8, 8, 0x01);
}

void Kit::setTargetKit (int targetKit)
{
    message.setBitRange (8 * 8, 8, targetKit);
}

} } }
