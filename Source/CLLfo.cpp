/*
  ==============================================================================

    CLLfo.cpp
    Created: 29 Nov 2022 7:13:34pm
    Author:  Chris

  ==============================================================================
*/

#include "CLLfo.h"
#include "JuceHeader.h"

CLLfo::CLLfo()
{
    reset();
}

CLLfo::~CLLfo()
{

}

void CLLfo::reset()
{
    mPhase = 0.0f;
    //zeromem(mBuffer, sizeof(float) * maxBufferSize); // Reset function that zeros out buffer
    memset(mBuffer, 0, sizeof(float) * kMaxChannelBufferSize); // Reset function that zeros out buffer
}

void CLLfo::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
    //reset();
}

void CLLfo::process(float inRate, float inDepth, int inNumSamples)
{
    const float rate = jmap(inRate, 0.0f, 1.0f, 0.01f, 10.0f); // Scale between 0.01 Hz to 10Hz

    for (int i = 0; i < inNumSamples; i++) {
        mPhase = mPhase + (rate / mSampleRate); // increment phase variable depending on smaple rate

        if (mPhase > 1.0f) { // if phase is greater than 1, wrap back around
            mPhase = mPhase - 1.0f;
        }

        const float lfoPosition = sinf(mPhase * cl2PI) * inDepth; // define the LFO & scale with depth param
        mBuffer[i] = lfoPosition;
    }

}

float* CLLfo::getBuffer()
{
    return mBuffer;
}
