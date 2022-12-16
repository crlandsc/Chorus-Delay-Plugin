/*
  ==============================================================================

    CLParameters.h
    Created: 10 Dec 2022 10:01:34am
    Author:  Chris

  ==============================================================================
*/

#pragma once

enum {
    kParameter_InputGain = 0,
    kParameter_ModulationRate,
    kParameter_ModulationDepth,
    kParameter_DelayTime,
    kParameter_DelayFeedback,
    kParameter_WetDry,
    kParameter_Type,
    kParameter_OutputGain,
    kParameter_TotalNumParameters
};

static String CLParameterID[kParameter_TotalNumParameters] =
{
    "InputGain",
    "ModulationRate",
    "ModulationDepth",
    "DelayTime",
    "DelayFeedback",
    "WetDry",
    "DelayType",
    "OutputGain"
};

static String CLParameterLabel[kParameter_TotalNumParameters] =
{
    "InputGain",
    "ModulationRate",
    "ModulationDepth",
    "DelayTime",
    "DelayFeedback",
    "WetDry",
    "DelayType",
    "OutputGain"
};

static float CLParameterDefaultValue[kParameter_TotalNumParameters] =
{
    0.5f,
    0.2f,
    1.0f,
    0.2f,
    0.5f,
    0.25f,
    0.0f,
    0.5f
};


