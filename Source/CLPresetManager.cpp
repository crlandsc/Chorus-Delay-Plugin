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

    // Preset directory path - Saves presets in "Documents" folder
    mPresetDirectory =
        File::getSpecialLocation(File::userDocumentsDirectory).getFullPathName() + directorySeparator + pluginName;

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
    /*
    const int numParameters = mProcessor->getNumParameters();

    for (int i = 0; i < numParameters; i++) {
        inElement->setAttribute(mProcessor->getParameterName(i),
            mProcessor->getParameter(i));
    }
    */

    XmlElement* presetName = new XmlElement("preset_name");

    presetName->setAttribute("name", mCurrentPresetName);

    inElement->addChildElement(presetName);

    auto& parameters = mProcessor->getParameters();

    for (int i = 0; i < parameters.size(); i++)
    {
        AudioProcessorParameterWithID* parameter =
            (AudioProcessorParameterWithID*)parameters.getUnchecked(i);

        inElement->setAttribute(parameter->paramID, parameter->getValue());
    }

}

void CLPresetManager::loadPresetForXml(XmlElement* inElement)
{

    /*
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
    */

    mCurrentPresetXml = inElement;

    XmlElement* presetName = inElement->getChildByName("preset_name");

    // early return if presetName element is nullptr
    if (presetName == nullptr) { return; }

    mCurrentPresetName = presetName->getStringAttribute("name", "error");

    // iterate our XML for attribute name and value
    auto& parameters = mProcessor->getParameters();

    for (int i = 0; i < mCurrentPresetXml->getNumAttributes(); i++) {

        const String paramId = mCurrentPresetXml->getAttributeName(i);
        const float value = mCurrentPresetXml->getDoubleAttribute(paramId);

        for (int j = 0; j < parameters.size(); j++) {

            AudioProcessorParameterWithID* parameter =
                (AudioProcessorParameterWithID*)parameters.getUnchecked(i);

            if (paramId == parameter->paramID) {
                parameter->setValueNotifyingHost(value);
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
    /*
    const int numParameters = mProcessor->getNumParameters();

    for (int i = 0; i < numParameters; i++) {
        mProcessor->setParameterNotifyingHost(i, mProcessor->getParameterDefaultValue(i));
    }

    mCurrentPresetIsSaved = false;
    mCurrentPresetName = "Untitled";
    */

    auto& parameters = mProcessor->getParameters();

    for (int i = 0; i < parameters.size(); i++) {

        AudioProcessorParameterWithID* parameter =
            (AudioProcessorParameterWithID*)parameters.getUnchecked(i);

        const float defaultValue =
            parameter->getDefaultValue();

        parameter->setValueNotifyingHost(defaultValue);
    }

    // update our bool
    mCurrentPresetIsSaved = false;
    mCurrentPresetName = "Untitled";

}

void CLPresetManager::savePreset()
{
    MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);

    // Deleter original file
    mCurrentlyLoadedPreset.deleteFile();

    // Append data
    mCurrentlyLoadedPreset.appendData(
        destinationData.getData(),
        destinationData.getSize());

    mCurrentPresetIsSaved = true;
}

void CLPresetManager::saveAsPreset(String inPresetName)
{
    File presetFile = File(mPresetDirectory + directorySeparator + inPresetName + PRESET_FILE_EXTENSION);

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
