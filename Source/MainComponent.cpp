#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
    
    auto syxFile = juce::File ("/Users/td/git/audio/elektron/SendKitTester/digitone_kit1_as2.syx");
    jassert (syxFile.existsAsFile());
    
    juce::MemoryBlock bytes;
    jassert (syxFile.loadFileAsData (bytes));

    auto inDevices = juce::MidiInput::getAvailableDevices();
    input = juce::MidiInput::openDevice (inDevices[1].identifier, this);
    input->start();

    auto outDevices = juce::MidiOutput::getAvailableDevices();
    output = juce::MidiOutput::openDevice (outDevices[1].identifier);
    
//    syxMessage = juce::MidiMessage::createSysExMessage (bytes.getData(), (int) bytes.getSize());
    
    getKit();
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::handleIncomingMidiMessage (juce::MidiInput* source,
                                               const juce::MidiMessage& message)
{
//    DBG (message.getDescription());
    
    if (message.isSysEx())
    {
        auto memoryBlock = juce::MemoryBlock (message.getSysExData(), message.getSysExDataSize());
        
        injectMidiControls (memoryBlock);
        injectTargetKit (memoryBlock, 1);
        injectChecksum (memoryBlock);

        syxMessage = juce::MidiMessage::createSysExMessage(memoryBlock.getData(), (int) memoryBlock.getSize());
        output->sendMessageNow (syxMessage);
        
    }
    else if (message.isProgramChange())
    {
        getKit();
//        output->sendMessageNow (syxMessage);
    }
}

void MainComponent::getKit()
{
    uint8_t request[13] = {0x00, 0x20, 0x3c, 0x0d, 0x00, 0x62, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x05};
    
    output->sendMessageNow (juce::MidiMessage::createSysExMessage (request, 13));
}

void MainComponent::injectMidiControls (juce::MemoryBlock& kitDump)
{
    // This sets MIDI T4 to output CC on channel 1
//    kitDump.setBitRange (0x913 * 8, 4 * 8, 0x20007f01);
    int start = 2321;
    kitDump.setBitRange (start * 8, 8, 0x20);
    kitDump.setBitRange ((start + 1) * 8, 8, 0x00);
    kitDump.setBitRange ((start + 2) * 8, 8, 0x7f);
    kitDump.setBitRange ((start + 3) * 8, 8, 0x01);
}

void MainComponent::injectChecksum (juce::MemoryBlock& message)
{
    int startByte = 9;
    int checksumBytes = 5;
    int total = 0;
    
    // Length is bytes 7 up to the end minus last 3 = size - 10
    // JUCE doesn't include f0/f7 in the message so we -8 instead
    auto messageSize = message.getSize() - 8;
    
    //Number(( & 16256) >> 7).toString(16)
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

void MainComponent::injectTargetKit (juce::MemoryBlock& message, int targetKit)
{
    message.setBitRange (8 * 8, 8, targetKit);
}
