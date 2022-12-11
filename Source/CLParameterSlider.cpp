/*
  ==============================================================================

    CLParameterSlider.cpp
    Created: 10 Dec 2022 10:40:57am
    Author:  Chris

  ==============================================================================
*/


#include "CLParameterSlider.h"

CLParameterSlider::CLParameterSlider(AudioProcessorValueTreeState& stateToControl,
    const String& parameterID,
    const String& parameterLabel)
    : juce::Slider(parameterLabel)
{

    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);
    setRange(0.f, 1.f, 0.001f);

    mAttachment =
        std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(stateToControl, parameterID, *this);

    /*
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);
    setRange(0.f, 1.f, 0.001f); // Increments 0-1 at 0.001 per step

    // -- THIS IS WHERE THE ISSUE IS -- //


    mAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(stateToControl, parameterID, *this);
    //mAttachment = AudioProcessorValueTreeState::SliderAttachment(stateToControl, parameterID, *this);

    // -- ------------------------ -- //
    */
}

CLParameterSlider::~CLParameterSlider()
{
}




/*
#include "CLParameterSlider.h"

CLParameterSlider::CLParameterSlider(AudioProcessorValueTreeState& stateToControl,
    const String& parameterID,
    const String& parameterLabel)
    : juce::Slider(parameterLabel)
{
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);
    setRange(0.f, 1.f, 0.001f);

    mAttachment =
        std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(stateToControl, parameterID, *this);
}

CLParameterSlider::~CLParameterSlider()
{
}

*/
