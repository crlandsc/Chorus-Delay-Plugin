/*
  ==============================================================================

    CLPresetManager.cpp
    Created: 16 Dec 2022 7:24:36am
    Author:  Chris

  ==============================================================================
*/

#include "CLPresetManager.h"

#if JUCE_WINDOWS
    static const String directorySeparator = "\\";
#elif JUCE_MAC
    static const String directorySeparator = "/";
#endif


CLPresetManager::CLPresetManager(AudioProcessor* inProcessor)
    : mCurrentPresetIsSaved(false),
    mCurrentPresetName("Untitled"),
    mProcessor(inProcessor)
{
    const String pluginName = (String)mProcessor->getName(); // Store name of plugin

    mPresetDirectory = File::getSpecialLocation(File::userDesktopDirectory).getFullPathName() + pluginName; // preset directory path

    // Check if directory exists
    if (!File(mPresetDirectory).exists()) {
        File(mPresetDirectory).createDirectory();
    }

    storeLocalPresets(); // Iterate through directory to store presets locally
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

int CLPresetManager::getNumberOfPresets()
{
    return mLocalPresets.size();
}

String CLPresetManager::getPresetName(int inPresetIndex)
{
    return mLocalPresets[inPresetIndex].getFileNameWithoutExtension();
}

void CLPresetManager::createNewPreset()
{
    const int numParameters = mProcessor->getNumParameters();

    for (int i = 0; i < numParameters; i++) {
        mProcessor->setParameterNotifyingHost(i, mProcessor->getParameterDefaultValue(i));
    }

    mCurrentPresetIsSaved = false;
    mCurrentPresetName = "Untitled";
}

void CLPresetManager::savePreset()
{
    MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);

    mCurrentlyLoadedPreset.deleteFile();

    mCurrentlyLoadedPreset.appendData(
        destinationData.getData(),
        destinationData.getSize());

    mCurrentPresetIsSaved = true;
}

void CLPresetManager::saveAsPreset(String inPresetName)
{
    File presetFile = File(mPresetDirectory + directorySeparator + inPresetName);

    if (!presetFile.exists()) {
        presetFile.create();
    }
    else {
        presetFile.deleteFile();
    }

    MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);

    presetFile.appendData(
        destinationData.getData(),
        destinationData.getSize());

    mCurrentPresetIsSaved = true;
    mCurrentPresetName = inPresetName;

    storeLocalPresets();
}

void CLPresetManager::loadPreset(int inPresetIndex)
{
    mCurrentlyLoadedPreset = mLocalPresets[inPresetIndex];

    MemoryBlock presetBinary;

    // If preset exists, then load
    if (mCurrentlyLoadedPreset.loadFileAsData(presetBinary)) {
        mCurrentPresetIsSaved = true;
        mCurrentPresetName = getPresetName(inPresetIndex);
        mProcessor->setStateInformation( // set state info for preset
            presetBinary.getData(),
            (int)presetBinary.getSize());
    }
}

bool CLPresetManager::getIsCurrentPresetSave()
{
    return mCurrentPresetIsSaved;
}

String CLPresetManager::getCurrentPresetName()
{
    return mCurrentPresetName;
}

void CLPresetManager::storeLocalPresets()
{
    mLocalPresets.clear();

    // Iterate through directory
    for (DirectoryIterator di( // di = directory iterator
        File(mPresetDirectory),
        false,
        "*" + (String)PRESET_FILE_EXTENSION,
        File::TypesOfFileToFind::findFiles); di.next();)
    {
        File preset = di.getFile();
        mLocalPresets.add(preset);
    }
}
