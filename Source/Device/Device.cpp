#include "Device.h"

#include "../Sysex/Request.h"

namespace Kompanion
{
namespace Device
{
    Device::Device (juce::String defaultMidiDeviceName,
                    uint8_t deviceSysexId): defaultMidiDeviceName (defaultMidiDeviceName),
                                            deviceSysexId (deviceSysexId)
    {
        initialiseDefaultMidiDevices();

        /*patternChangeCallbacks.emplace_back ([this] (int lastPattern, int currentPattern)
                                             {
                                                 DBG ("Pattern change from " << lastPattern << " to " << currentPattern);
                                                 return true;
                                             });*/

        /*kitCallbacks.emplace_back ([this] (std::unique_ptr<Sysex::KitBase> kit)
                                   {
                                       DBG ("Received kit from device");
                                       return true;
                                   });*/
    }

    void Device::initialiseDefaultMidiDevices()
    {
        juce::MidiDeviceInfo inputInfo;

        for (auto& info: juce::MidiInput::getAvailableDevices())
        {
            if (info.name == defaultMidiDeviceName)
                inputInfo = info;
        }
        jassert (inputInfo.identifier != "");

        midiInput = juce::MidiInput::openDevice (inputInfo.identifier, this);
        jassert (midiInput != nullptr);

        juce::MidiDeviceInfo outputInfo;

        for (auto& info: juce::MidiOutput::getAvailableDevices())
        {
            if (info.name == defaultMidiDeviceName)
                outputInfo = info;
        }
        jassert (outputInfo.identifier != "");

        midiOutput = juce::MidiOutput::openDevice (outputInfo.identifier);
        jassert (midiOutput != nullptr);

        midiInput->start();
    }

    void Device::addKitCallback (KitCallback callback)
    {
        addCallback (callback, kitCallbacks);
    }

    void Device::addPatternChangeCallback (PatternChangeCallback callback)
    {
        addCallback (callback, patternChangeCallbacks);
    }

    void Device::requestKit (int index)
    {
        DBG ("requestKit " << index);

        Sysex::Request request (deviceSysexId, 0x62, index);

        sendMessage (request.getMessage());
    }

    void Device::sendMessage (const juce::MidiMessage& message)
    {
        midiOutput->sendMessageNow (message);
    }

    void Device::handleIncomingMidiMessage (juce::MidiInput* source, const juce::MidiMessage& message)
    {
        DBG ("Received MIDI: " << message.getDescription());

        if (message.isProgramChange())
        {
            auto lastPattern = currentPattern;
            currentPattern = message.getProgramChangeNumber();
            callCallbacks (patternChangeCallbacks, lastPattern, currentPattern);
        }
        else if (message.isSysEx())
        {
            auto memoryBlock = juce::MemoryBlock (message.getSysExData(), static_cast<size_t> (message.getSysExDataSize()));

            if (message.getSysExData()[5] == 0x52)
            {
                callCallbacks (kitCallbacks, createKit (memoryBlock));
            }
        }
    }

}// namespace Device
}// namespace Kompanion
