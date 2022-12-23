/*
  ==============================================================================

    CLParameterSlider.h
    Created: 10 Dec 2022 10:40:57am
    Author:  Chris

  ==============================================================================
*/


#pragma once

#include "JuceHeader.h"

class CLParameterSlider :
    public Slider
{
public:

    CLParameterSlider(AudioProcessorValueTreeState& stateToControl,
        const String& parameterID,
        const String& parameterLabel);

    ~CLParameterSlider();

private:

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CLParameterSlider); // detect memory leaks
};

