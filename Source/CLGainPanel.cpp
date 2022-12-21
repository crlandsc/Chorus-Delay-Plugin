/*
  ==============================================================================

    CLGainPanel.cpp
    Created: 9 Dec 2022 5:57:52pm
    Author:  Chris

  ==============================================================================
*/


#include "CLGainPanel.h"
#include "CLParameters.h"
#include "CLHelperFunctions.h"

CLGainPanel::CLGainPanel(ChorusDelayAudioProcessor* inProcessor) :
    CLPanelBase(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH,
        GAIN_PANEL_HEIGHT);

    const int meter_width = 64;
    mVuMeter = std::make_unique<CLVuMeter>(mProcessor);
    mVuMeter->setBounds(
        (getWidth() * 0.5) - (meter_width * 0.5),
        (getHeight() * 0.55) - (meter_width * 0.5),
        meter_width,
        getHeight() * 0.45);

    addAndMakeVisible(mVuMeter.get());
}

CLGainPanel::~CLGainPanel()
{

}

void CLGainPanel::paint(Graphics& g) // Add slider labels
{
    CLPanelBase::paint(g);

    if (mGainSlider) {
        paintComponentLabel(g, mGainSlider.get());
    }
}

void CLGainPanel::setParameterID(int inParameterID)
{
    //mGainSlider.reset();

    mGainSlider = std::make_unique<CLParameterSlider>(
        mProcessor->parameters,
        CLParameterID[inParameterID],
        CLParameterLabel[inParameterID]);

    const int slider_size = 54; // size of slide (pixels)

    mGainSlider->setBounds(
        (getWidth() * 0.5) - (slider_size * 0.5),
        (getHeight() * 0.2) - (slider_size * 0.5) - 10,
        slider_size,
        slider_size);
    addAndMakeVisible(mGainSlider.get());

    mVuMeter->setParameterID(inParameterID);

}




/*
#include "CLGainPanel.h"


CLGainPanel::CLGainPanel(ChorusDelayAudioProcessor* processor)
    : CLPanelBase(processor)
{
    setSize(GAIN_PANEL_WIDTH,
        GAIN_PANEL_HEIGHT);
}

CLGainPanel::~CLGainPanel()
{
}

void CLGainPanel::paint(Graphics& g)
{
    CLPanelBase::paint(g);

    paintComponentLabel(g, mGain.get());
}

void CLGainPanel::setParameterID(int inParameterID)
{
    mGain = std::make_unique<CLParameterSlider>(mProcessor->parameters,
        CLParameterID[inParameterID],
        CLParameterLabel[inParameterID]);
    const int slider_size = 54;
    mGain->setBounds(getWidth() * 0.5 - slider_size * 0.5,
        slider_size * 0.5,
        slider_size,
        slider_size);
    addAndMakeVisible(mGain.get());

}
*/
