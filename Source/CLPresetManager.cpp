/*
  ==============================================================================

    CLPresetManager.cpp
    Created: 16 Dec 2022 7:24:36am
    Author:  Chris

  ==============================================================================
*/

#include "CLPresetManager.h"

CLPresetManager::CLPresetManager(AudioProcessor* inProcessor)
    : mProcessor(inProcessor)
{

}

CLPresetManager::~CLPresetManager()
{

}

void CLPresetManager::getXmlForPreset(XmlElement* inElement)
{
    const int numParameters = mProcessor->getNumParameters();

    for (int i = 0; i < numParameters; i++) {
        inElement->setAttribute(mProcessor->getParameterName(i),
            mProcessor->getParameter(i));
    }
}

void CLPresetManager::loadPresetForXml(XmlElement* inElement)
{
    mCurrentPresetXml = inElement;

    const int numParameters = mProcessor->getNumParameters();

    for (int i = 0; i < numParameters; i++) {
        
        const String name = mCurrentPresetXml->getAttributeName(i);
        const float value = mCurrentPresetXml->getDoubleAttribute(name);

        for (int j = 0; j < numParameters; j++) {
            if (mProcessor->getParameterName(j) == name) {
                mProcessor->setParameterNotifyingHost(j, value);
            }
        }
    }

}
