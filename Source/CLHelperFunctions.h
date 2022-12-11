/*
  ==============================================================================

    CLHelperFunctions.h
    Created: 11 Dec 2022 10:56:16am
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "CLInterfaceDefines.h"

/** KAP NaN Macro -- we'll assert if we hit a NaN, so we can break before the code crashes. */
#define kapassert_isnan(expression)  jassert(!isnan(expression))

inline void paintComponentLabel(Graphics& g, Component* inComponent)
{
    const int x = inComponent->getX();
    const int y = inComponent->getY() + inComponent->getHeight();
    const int w = inComponent->getWidth();
    const int h = 20;
    const String label = inComponent->getName();
    const float cornerSize = 3.f;
    
    g.setColour (CLColour_3);
    g.fillRoundedRectangle (juce::Rectangle<float>(x,y,w,h),
                            cornerSize);
    
    g.setColour(CLColour_1);
    g.setFont(font_1);
    g.drawFittedText(label, x, y, w, h, Justification::centred, 1);
}
