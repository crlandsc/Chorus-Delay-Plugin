/*
  ==============================================================================

    CLGain.h
    Created: 29 Nov 2022 7:13:24pm
    Author:  Chris

  ==============================================================================
*/

#pragma once

class CLGain
{
public:
    CLGain();
    ~CLGain();

    void process(float* inAudio, // Incoming audio
                        float inGain, // The gain input
                        float* outAudio, // Outgoing audio
                        float inNumSamplesToRender); // block size (not guarunteed, so it needs to be specified)

private:

};