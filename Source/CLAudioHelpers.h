/*
  ==============================================================================

    CLAudioHelpers.h
    Created: 29 Nov 2022 7:12:53pm
    Author:  Chris

  ==============================================================================
*/

#pragma once

#define clParameterSmoothingCoeff_Generic 0.04
#define clParameterSmoothingCoeff_Fine 0.002

const static int maxBufferSize = 192000; // Needs to be larger than the max delay time. Better to implement with smaller buffers

const static double clPI = 3.1415926535897932384626433832795028841968;
const static double cl2PI = 6.2831853071795864769252867665590057683943;

// Linear interpolation function
inline float cl_linear_interpolation(float v0, float v1, float t) // compiles within the class it is used
{
    return (1 - t) * v0 + t * v1; // standard linear interpolation function
}
