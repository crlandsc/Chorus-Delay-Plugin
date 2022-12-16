/*
  ==============================================================================

    CLPresetManager.h
    Created: 16 Dec 2022 7:24:36am
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class CLPresetManager
{
public:

    CLPresetManager(AudioProcessor* inProcessor);

    ~CLPresetManager();

    void getXmlForPreset(XmlElement* inElement);

    void loadPresetForXml(XmlElement* inElement);

private:

    XmlElement* mCurrentPresetXml;

    AudioProcessor* mProcessor;

};