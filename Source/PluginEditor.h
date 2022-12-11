/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "CLMainPanel.h"

//==============================================================================
/**
*/
class ChorusDelayAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ChorusDelayAudioProcessorEditor (ChorusDelayAudioProcessor&);
    ~ChorusDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    std::unique_ptr<CLMainPanel> mMainPanel;
    std::unique_ptr<CLParameterSlider> mParameterSlider[kParameter_TotalNumParameters];
    std::unique_ptr<Label> mLabel[kParameter_TotalNumParameters];

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ChorusDelayAudioProcessor& audioProcessor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusDelayAudioProcessorEditor)
};
