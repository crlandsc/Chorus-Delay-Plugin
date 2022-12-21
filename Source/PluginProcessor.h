/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CLParameters.h"
#include "CLPresetManager.h"

#include "CLGain.h"
#include "CLDelay.h"
#include "CLLfo.h"


//==============================================================================
/**
*/
class ChorusDelayAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    ChorusDelayAudioProcessor();
    ~ChorusDelayAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float getInputGainMeterLevel(int inChannel);
    float getOutputGainMeterLevel(int inChannel);

    AudioProcessorValueTreeState parameters;

    CLPresetManager* getPresetManager();

private:

    // Internal
    void initializeDSP(); // initializes all processes

    // Internal
    void initializeParameters(); // Initialize all parameters

    std::unique_ptr<CLPresetManager> mPresetManager; // Preset Manager

    std::unique_ptr<CLGain> mInputGain [2]; // Input gain. Process L and R channels independently. Could implement interleaved if desired.
    std::unique_ptr<CLGain> mOutputGain [2]; // Output gain
    std::unique_ptr<CLDelay> mDelay[2]; // Delay object
    std::unique_ptr<CLLfo> mLfo[2];

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusDelayAudioProcessor)
};
