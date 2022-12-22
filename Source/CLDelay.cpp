/*
  ==============================================================================

    CLDelay.cpp
    Created: 29 Nov 2022 7:13:16pm
    Author:  Chris

  ==============================================================================
*/

#include "JuceHeader.h" // Put header in .cpp rather than header to avoid long compile times
#include "CLDelay.h" // include header
#include "CLAudioHelpers.h" // include helper functions

CLDelay::CLDelay()
    : mSampleRate(-1), // Cannot have a negative sample rate - set as a check to force crash unless initialize setSampleRate
    mFeedbackSample(0.0),
    mTimeSmoothed(0),
    mDelayIndex(0)
{

}
CLDelay::~CLDelay()
{
}

void CLDelay::setSampleRate(double inSampleRate) // host typically represents the sample rate as a double
{
    mSampleRate = inSampleRate;
    reset();
}

void CLDelay::reset()
{
    mTimeSmoothed = 0.0f;

    //zeromem(mBuffer, sizeof(double) * maxBufferSize); // Reset function that zeros out buffer
    memset(mBuffer, 0, sizeof(double) * kMaxChannelBufferSize); // Reset function that zeros out buffer 
}

void CLDelay::process(float* inAudio,
    float inTime,
    float inFeedback,
    float inWetDry,
    float inType,
    float* inModulationBuffer,
    float* outAudio,
    int inNumSamplesToRender)
{
    const float wet = inWetDry;
    const float dry = 1.f - wet;
    const float feedbackMapped = (inType == kCLType_Delay) ? jmap(inFeedback, 0.f, 1.f, 0.f, 1.2f) : 0.f; // Map feedback 1-1.2 to allow for soft clipping

    for (int i = 0; i < inNumSamplesToRender; i++) {

        if ((int)inType == kCLType_Delay) {
            mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Fine * (mTimeSmoothed - inTime); // Implement time smoothing each time process block is called
        }
        else {
            const double delayTimeModulation = (0.003 + 0.002 * inModulationBuffer[i]); // Calculate modulation for delay
            mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Fine * (mTimeSmoothed - delayTimeModulation); // Implement time smoothing each time process block is called
        }
       
        const double delayTimeInSamples = (mTimeSmoothed * mSampleRate); // Converting the delay time into samples
        const double sample = getInterpolatedSample(delayTimeInSamples); //  get the interpolated sample

        // add the delayed sample to the buffer
        // Wrap in tanh_clip function to allow for "soft clipping" over 100% feeback
        mBuffer[mDelayIndex] = tanh_clip(inAudio[i] + (mFeedbackSample * feedbackMapped));

        mFeedbackSample = sample; // assign the current sample to the feedback sample

        outAudio[i] = (inAudio[i] * dry + sample * wet); // output = mix of dry & wet signal

        mDelayIndex = mDelayIndex + 1; // step delay index

        if (mDelayIndex >= kMaxChannelBufferSize) { // Check to make sure that the delay index is within buffer
            mDelayIndex = mDelayIndex - kMaxChannelBufferSize;
        }
    }
}

double CLDelay::getInterpolatedSample(float inDelayTimeInSamples)
{
    double readPosition = (double)mDelayIndex - inDelayTimeInSamples;

    if (readPosition < 0.0f) {
        readPosition = readPosition + kMaxChannelBufferSize;
    }

    // Circular buffer indexes
    int index_y0 = (int)readPosition - 1;
    if (index_y0 < 0) { // Check to make sure that the index is not outside of the circular buffer's bounds
        index_y0 = index_y0 + kMaxChannelBufferSize; // if index less than 0, then "loop" the value back to end of buffer
    }

    int index_y1 = readPosition;
    if (index_y1 >= kMaxChannelBufferSize) { // Check to make sure that the index is not outside of the circular buffer's bounds
        index_y1 = index_y1 - kMaxChannelBufferSize; // if index greater than end of the buffer, then "loop" the value back to the beginning of buffer
    }

    // read samples from circular buffer indexes
    const float sample_y0 = mBuffer[index_y0];
    const float sample_y1 = mBuffer[index_y1];
    const float mu = readPosition - (int)readPosition; // fractional different of read position (for linear interpolation)

    // Linera interpolation from CLAudioHelper.h
    double outSample = cl_linear_interpolation(sample_y0, sample_y1, mu);
    return outSample;
}

