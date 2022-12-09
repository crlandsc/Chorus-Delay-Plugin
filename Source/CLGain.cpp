/*
  ==============================================================================

    CLGain.cpp
    Created: 29 Nov 2022 7:13:24pm
    Author:  Chris

  ==============================================================================
*/

#include "CLGain.h"

#include "JuceHeader.h" // Includes STL

CLGain::CLGain()
{

}

CLGain::~CLGain()
{

}

void CLGain::process(float* inAudio, // Incoming audio
                    float inGain, // The gain input
                    float* outAudio, // Outgoing audio
                    float inNumSamplesToRender) // block size (not guarunteed, so it needs to be specified)
{
    float gainMapped = jmap(inGain, 0.0f, 1.0f, -24.0f, 24.0f); // mapping input gain (0,1) to (-24,24)
    gainMapped = Decibels::decibelsToGain(gainMapped, -24.0f); // mapping gain to decibels

    for (int i = 0; i < inNumSamplesToRender; i++) {
        outAudio[i] = inAudio[i] * gainMapped; // multiply signal by the gain number
    };


}
