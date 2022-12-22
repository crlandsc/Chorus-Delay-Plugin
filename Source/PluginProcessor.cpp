/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "CLParameters.h"

// Initialize Parameters
/** (Need to do this pre - constructor otherwise unhandled exception thrown for
"this" being a nullptr) */
AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    std::vector<std::unique_ptr<AudioParameterFloat>> params;

    for (int i = 0; i < kParameter_TotalNumParameters; i++) {

        params.push_back(std::make_unique<AudioParameterFloat>(
            CLParameterID[i],
            CLParameterID[i], // Can't put CLParameterLabel[i] here because of spaces in enum names
            NormalisableRange<float>(0.0f, 1.0f),
            CLParameterDefaultValue[i]));
    }

    return { params.begin(), params.end() };
}

//==============================================================================
ChorusDelayAudioProcessor::ChorusDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
        parameters(
            *this,
            nullptr, //null pointer to undoManager (optional)
            juce::Identifier("CL"), // valueTree identifier
            createParameterLayout()) // initialize parameters
#endif
{
    //initializeParameters(); // Call before DSP in case DSP relies on a parameter

    initializeDSP();

    mPresetManager = std::make_unique<CLPresetManager>(this); // Pass processor into preset manager
}

ChorusDelayAudioProcessor::~ChorusDelayAudioProcessor()
{
}

//==============================================================================
const juce::String ChorusDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChorusDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ChorusDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ChorusDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ChorusDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChorusDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ChorusDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChorusDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ChorusDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void ChorusDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ChorusDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    // 
    // Set the sample rate when prepareToPlay is called
    for (int i = 0; i < 2; i++) {
        mDelay[i]->setSampleRate(sampleRate);
        mLfo[i]->setSampleRate(sampleRate);
    }
}

void ChorusDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    for (int i = 0; i < 2; i++) {
        mDelay[i]->reset();
        mLfo[i]->reset();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChorusDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ChorusDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    //parameters.state = ValueTree(Identifier("CLParameter")); // Initialize outside of for loop. Attempting to avoid Reaper crashes

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        mInputGain[channel]->process(channelData,
            getParameter(kParameter_InputGain),
            channelData,
            buffer.getNumSamples());

        float rate = channel == 1 ? 0 : getParameter(kParameter_ModulationRate); // Only modulate 1 channel to make a chorus (L unaffected, R modulated)

        mLfo[channel]->process(rate,
            getParameter(kParameter_ModulationDepth),
            buffer.getNumSamples());

        mDelay[channel]->process(channelData,
            getParameter(kParameter_DelayTime),
            getParameter(kParameter_DelayFeedback),
            getParameter(kParameter_WetDry),
            getParameter(kParameter_Type),
            mLfo[channel]->getBuffer(),
            channelData,
            buffer.getNumSamples());

        mOutputGain[channel]->process(channelData,
            getParameter(kParameter_OutputGain),
            channelData,
            buffer.getNumSamples());

    }
}

//==============================================================================
bool ChorusDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ChorusDelayAudioProcessor::createEditor()
{
    return new ChorusDelayAudioProcessorEditor (*this);
}

//==============================================================================
void ChorusDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    DBG("ChorusDelayAudioProcessor::getStateInformation");

    XmlElement preset("CL_StateInfo");
    XmlElement* presetBody = new XmlElement("CL_Preset");

    mPresetManager->getXmlForPreset(presetBody);

    preset.addChildElement(presetBody);
    copyXmlToBinary(preset, destData);

}

void ChorusDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    const auto xmlState = getXmlFromBinary(data, sizeInBytes); // retrive xml from stored binary data

    jassert(xmlState.get() != nullptr); // break if nullptr

    // Load presets
    for (auto* subchild : xmlState->getChildIterator()) {
        mPresetManager->loadPresetForXml(subchild);
    }

    // --- Don't use smart pointers --- //
    //std::unique_ptr<XmlElement> xmlState = std::make_unique<XmlElement>(getXmlFromBinary(data, sizeInBytes)); // Creates an XML element from the raw data being passed into setStateInformation
    //XmlElement* xmlState = getXmlFromBinary(data, sizeInBytes).get(); // retrive xml from stored binary data (need .get() because JUCE class in uniqque_ptr)

    // Load presets
    //if (xmlState) {
    //    forEachXmlChildElement(xmlState.get(), subChild) { // Juce macro to iterate over the xml element
    //        mPresetManager->loadPresetForXml(subChild);
    //    }
    //}
    //else { // If nullptr
    //    jassertfalse;
    //}

}

float ChorusDelayAudioProcessor::getInputGainMeterLevel(int inChannel)
{
    const float normalizeddB = dBToNormalizedGain(mInputGain[inChannel]->getMeterLevel());

    return normalizeddB;
}

float ChorusDelayAudioProcessor::getOutputGainMeterLevel(int inChannel)
{
    const float normalizeddB = dBToNormalizedGain(mOutputGain[inChannel]->getMeterLevel());

    return normalizeddB;
}

CLPresetManager* ChorusDelayAudioProcessor::getPresetManager()
{
    return mPresetManager.get();
}

void ChorusDelayAudioProcessor::initializeDSP()
{
    // Processing in stereo currently. To include multi-out later
    for (int i = 0; i < 2; i++) {
        mInputGain[i] = std::make_unique<CLGain>(); //  initialize gain
        mDelay[i] = std::make_unique<CLDelay>(); // initialize delay
        mLfo[i] = std::make_unique<CLLfo>(); // initialize LFO
        mOutputGain[i] = std::make_unique<CLGain>(); //  initialize gain
    }

}

void ChorusDelayAudioProcessor::initializeParameters()
{
    /*
    for (int i = 0; i < kParameter_TotalNumParameters; i++) {
        parameters.createAndAddParameter(
            CLParameterID[i],
            CLParameterID[i],
            CLParameterID[i],
            NormalisableRange<float>(0.0f, 1.0f),
            0.5f,
            nullptr,
            nullptr);
    }

    parameters.state = ValueTree(Identifier("CLParameters")); // Identifier object as a constructor argument to initialize (Depricated)
    */
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChorusDelayAudioProcessor();
}
