/*
  ==============================================================================

    CLVuMeter.cpp
    Created: 20 Dec 2022 7:43:08pm
    Author:  Chris

  ==============================================================================
*/

#include "CLVuMeter.h"
#include "CLInterfaceDefines.h"
#include "CLParameters.h"

CLVuMeter::CLVuMeter(ChorusDelayAudioProcessor* inProcessor)
    : mParameterID(-1),
    mCh0Level(0),
    mCh1Level(0),
    inProcessor(inProcessor)
{

}

CLVuMeter::~CLVuMeter()
{

}

void CLVuMeter::paint(Graphics& g)
{
    const int meter_width = getWidth() / 4;

    g.setColour(CLColour_6);
    // Empty Left Channel
    g.fillRect((meter_width / 2), 0, meter_width, getHeight());
    // Empty Right Channel
    g.fillRect((meter_width / 2) + (meter_width * 2), 0, meter_width, getHeight());

    int ch0fill = getHeight() - (getHeight() * mCh0Level);
    int ch1fill = getHeight() - (getHeight() * mCh1Level);

    if (ch0fill < 0) {
        ch0fill = 0;
    }

    if (ch1fill < 0) {
        ch1fill = 0;
    }

    g.setColour(CLColour_7);
    // Filled Left channel
    g.fillRect((meter_width / 2), ch0fill, meter_width, getHeight());
    // Filled Right channel
    g.fillRect((meter_width / 2) + (meter_width * 2), ch1fill, meter_width, getHeight());
}

void CLVuMeter::timerCallback()
{
    float updateCh0Level = 0.0f;
    float updateCh1Level = 0.0f;

    switch (mParameterID)
    {
    case(kParameter_InputGain):
    {
        updateCh0Level = inProcessor->getInputGainMeterLevel(0);
        updateCh1Level = inProcessor->getInputGainMeterLevel(1);

    } break;
    case(kParameter_OutputGain):
    {
        updateCh0Level = inProcessor->getOutputGainMeterLevel(0);
        updateCh1Level = inProcessor->getOutputGainMeterLevel(1);

    } break;
    }


    if (updateCh0Level > mCh0Level) {
        mCh0Level = updateCh0Level;
    }
    else {
        mCh0Level = kMeterSmoothingCoeff * (mCh0Level - updateCh0Level) + updateCh0Level; // smoothing
    }

    if (updateCh1Level > mCh1Level) {
        mCh1Level = updateCh1Level;
    }
    else {
        mCh1Level = kMeterSmoothingCoeff * (mCh1Level - updateCh1Level) + updateCh1Level; // smoothing
    }

    // Denormalize levels (to make sure they are not too small). If not, then do not repaint.
    mCh0Level = cl_denormalize(mCh0Level);
    mCh1Level = cl_denormalize(mCh1Level);

    if (mCh0Level && mCh1Level) {
        repaint();
    }
}

void CLVuMeter::setParameterID(int inParameterID)
{
    mParameterID = inParameterID;

    startTimerHz(15); // refresh rate in Hz. Higher frequency = more load
}
