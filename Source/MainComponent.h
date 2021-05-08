#pragma once

#include <JuceHeader.h>

#include "Behaviour/KitLockBehaviour.h"
#include "Device/Digitone.h"
#include "Sysex/Digitone/Kit.h"

using namespace Kompanion;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    Device::Digitone device;
    std::vector<std::unique_ptr<Behaviour::BehaviourBase>> behaviours;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
