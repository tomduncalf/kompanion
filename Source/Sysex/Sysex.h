/*
  ==============================================================================

    Sysex.h
    Created: 2 May 2021 6:07:57pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace Kompanion { namespace Sysex {

class Sysex
{
public:
    Sysex (juce::MemoryBlock message);
    
    juce::MidiMessage getMessage();
    
protected:
    juce::MemoryBlock message;
    
private:
    void injectChecksum();
};

} }
