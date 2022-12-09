/*
  ==============================================================================

    CLLfo.h
    Created: 29 Nov 2022 7:13:34pm
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include "CLAudioHelpers.h"

class CLLfo
{
public:
    CLLfo();
    ~CLLfo();

    void reset();

    void setSampleRate(double inSampleRate);

    void process(float inRate, float inDepth, int inNumSamples); // processing. Creates buffer internally

    float* getBuffer();

private:

    double mSampleRate; // sample rate

    float mPhase; // phase

    float mBuffer[maxBufferSize]; // internal buffer
};
