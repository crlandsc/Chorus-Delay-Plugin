/*
  ==============================================================================

    CLAudioHelpers.h
    Created: 29 Nov 2022 7:12:53pm
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include <cmath>
#include "JuceHeader.h"

// Max buffer size
#define kMaxChannelBufferSize 192000

// Max num channels
#define kMaxNumChannels 8

#define kParameterSmoothingCoeff_Generic 0.04
#define kParameterSmoothingCoeff_Fine 0.002
#define kMeterSmoothingCoeff 0.2

static const double clPIHalf = 1.5707963267948966192313216916397514420985846996;
const static double clPI = 3.1415926535897932384626433832795028841968;
const static double cl2PI = 6.2831853071795864769252867665590057683943;

static inline float dBToNormalizedGain(float inValue)
{
    float inValuedB = Decibels::gainToDecibels(inValue + 0.00001f); // avoid becoming -inf
    inValuedB = (inValuedB + 96.0f) / 96.0f; // Higher values = smoother VU meter readings

    return inValuedB;
}

// Linear interpolation function
// (https://en.wikipedia.org/wiki/Linear_interpolation)
inline float cl_linear_interpolation(float v0, float v1, float t) // compiles within the class it is used
{
    return (1 - t) * v0 + t * v1; // standard linear interpolation function
}

// Prevent tiny numbers
inline float cl_denormalize(float inValue)
{
    float absValue = fabs(inValue);

    // < 0.000000000000001
    if (absValue < 1e-15)
    {
        return 0.0f;
    }
    else {
        return inValue;
    }
}

// Rational tanh Approximation - Used to allow for feedback to exceed 100% 
// (https://www.musicdsp.org/en/latest/Other/238-rational-tanh-approximation.html?highlight=tanh*/)
inline double tanh_clip(double x)
{
    return x * (27 + x * x) / (27 + 9 * x * x);
}
