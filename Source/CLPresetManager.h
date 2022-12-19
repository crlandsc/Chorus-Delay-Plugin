/*
  ==============================================================================

    CLPresetManager.h
    Created: 16 Dec 2022 7:24:36am
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define PRESET_FILE_EXTENSION ".cpf" 

class CLPresetManager
{
public:

    CLPresetManager(AudioProcessor* inProcessor);

    ~CLPresetManager();

    void getXmlForPreset(XmlElement* inElement);

    void loadPresetForXml(XmlElement* inElement);

    int getNumberOfPresets(); // return the number of presets

    String getPresetName(int inPresetIndex); // return the current preset name

    void createNewPreset(); // create a new preset

    void savePreset(); // Save a preset

    void saveAsPreset(String inPresetName); // Save a new preset

    void loadPreset(int inPresetIndex); // Load a preset via index

    bool getIsCurrentPresetSave(); // Determine if preset is to be saved or save as

    String getCurrentPresetName(); // Returns the name of the current preset

private:

    void storeLocalPresets(); // Used for storing all presets on disk in the memory of the preset manager

    bool mCurrentPresetIsSaved; // Is current preset saved?

    File mCurrentlyLoadedPreset; // Represents currently loaded preset

    Array<File> mLocalPresets; // Array of local presets

    String mCurrentPresetName; // Current preset name

    String mPresetDirectory; // Path of directory to the presets

    XmlElement* mCurrentPresetXml;

    AudioProcessor* mProcessor;

};