/*
  ==============================================================================

    CLCenterPanelMenuBar.h
    Created: 9 Dec 2022 5:57:27pm
    Author:  Chris

  ==============================================================================
*/

#pragma once
#include "CLPanelBase.h"
#include "CLParameterComboBox.h"

class CLCenterPanelMenuBar :
    public CLPanelBase
{
public:

    CLCenterPanelMenuBar(ChorusDelayAudioProcessor* inProcessor);
    ~CLCenterPanelMenuBar();

    void addFxTypeComboBoxListener(ComboBox::Listener* inListener);
    void removeFxTypeComboBoxListener(ComboBox::Listener* inListener);

private:

    std::unique_ptr<CLParameterComboBox> mFxTypeComboBox;

};