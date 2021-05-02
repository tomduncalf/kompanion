/*
  ==============================================================================

    Sysex.cpp
    Created: 2 May 2021 6:07:57pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#include "Sysex.h"

namespace Kompanion { namespace Sysex {

Sysex::Sysex (juce::MemoryBlock message) : message (message) {}

juce::MidiMessage Sysex::getMessage()
{
    injectChecksum();
    
    return juce::MidiMessage::createSysExMessage (message.getData(), (int) message.getSize());
}

void Sysex::injectChecksum()
{
    int startByte = 9;
    int checksumBytes = 5;
    int total = 0;
    
    // Length is bytes 7 up to the end minus last 3 = size - 10
    // JUCE doesn't include f0/f7 in the message so we -8 instead
    auto messageSize = message.getSize() - 8;
    
    int messageLengthByte1 = (messageSize & 0b11111110000000) >> 7; // bits 7-13
    int messageLengthByte2 = (messageSize & 0b1111111); // bits 0-6

    int currentByte = -1;
    for (auto byte : message)
    {
        currentByte++;
        
        if (currentByte < startByte) continue;
        if (currentByte > message.getSize() - checksumBytes) continue;
        
        total += byte;
    }
    
    auto checksumByte1 = (total & 0b11111110000000) >> 7; // bits 7-13
    auto checksumByte2 = (total & 0b1111111); // bits 0-6
    
    size_t start = message.getSize() - 4;
    message.setBitRange (start * 8, 8, checksumByte1);
    message.setBitRange ((start + 1) * 8, 8, checksumByte2);
    message.setBitRange ((start + 2) * 8, 8, messageLengthByte1);
    message.setBitRange ((start + 3) * 8, 8, messageLengthByte2);
}

} }
