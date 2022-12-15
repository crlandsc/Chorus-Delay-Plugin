/*
  ==============================================================================

    CLDelay.h
    Created: 29 Nov 2022 7:13:16pm
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "CLAudioHelpers.h"

enum CLType
{
    kCLType_Delay = 0,
    kCLType_Chorus,
};

class CLDelay
{
public:
    CLDelay();
    ~CLDelay();

    void setSampleRate(double inSampleRate); // host typically represents the sample rate as a double

    void reset();

    void process(float* inAudio, // Audio in
        float inTime, // Delay time in
        float inFeedback, // Feedback in
        float inWetDry, // Wet/dry blend
        float inType, // which type (Delay/Chorus)
        float* inModulationBuffer, // Connect LFO modulation to delay
        float* outAudio, // Audio out
        int inNumSamplesToRender); // block size

private:
    // Internal
    double getInterpolatedSample(float inDelayTimeInSamples); // Linear interpolation (to avoid discontinuities)

    double mSampleRate;
    double mBuffer[maxBufferSize]; // buffer size to be updated later
    double mFeedbackSample;

    float mTimeSmoothed; // A smoothed version of the "inTime" argument in the process function

    int mDelayIndex;

};