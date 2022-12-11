/*
  ==============================================================================

    CLParameterComboBox.cpp
    Created: 10 Dec 2022 10:41:13am
    Author:  Chris

  ==============================================================================
*/

#include "CLParameterComboBox.h"

CLParameterComboBox::CLParameterComboBox(AudioProcessorValueTreeState& stateToControl,
    const String& parameterID) :
    juce::ComboBox(parameterID)
{
    mAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(stateToControl, parameterID, *this);
}

CLParameterComboBox::~CLParameterComboBox()
{
}
