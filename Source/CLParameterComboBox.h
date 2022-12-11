/*
  ==============================================================================

    CLParameterComboBox.h
    Created: 10 Dec 2022 10:41:13am
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class CLParameterComboBox :
    public ComboBox
{
public:

    CLParameterComboBox(AudioProcessorValueTreeState& stateToControl, const String& parameterID);
    ~CLParameterComboBox();

private:

    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CLParameterComboBox); // detect memory leaks
};