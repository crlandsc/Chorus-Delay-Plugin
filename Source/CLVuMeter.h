/*
  ==============================================================================

    CLVuMeter.h
    Created: 20 Dec 2022 7:43:08pm
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

class CLVuMeter
    : public Component,
    public Timer
{
public:
    CLVuMeter(ChorusDelayAudioProcessor* inProcessor);
    ~CLVuMeter();

    void paint(Graphics& g) override;

    void timerCallback() override;

    void setParameterID(int inParameterID);

private:

    int mParameterID;

    float mCh0Level;
    float mCh1Level;

    ChorusDelayAudioProcessor* inProcessor;

};