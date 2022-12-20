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


inline void paintComponentLabel(Graphics& g, Component* inComponent)
{
    const int x = inComponent->getX() - (0.25f * inComponent->getWidth()); // shift X position to center label
    const int y = inComponent->getY() + inComponent->getHeight();
    const int w = inComponent->getWidth() * 1.5f; // 1.5 the width of component
    const int h = 20;
    const float cornerSize = 3.0f;
    const String label = inComponent->getName();

    g.setColour(CLColour_3);
    g.fillRoundedRectangle(x, y, w, h, cornerSize);

    g.setColour(Colours::darkgrey);
    g.setColour(CLColour_1);
    g.setFont(font_1);
    g.drawFittedText(label, x, y, w, h, Justification::centred, 1);
}

