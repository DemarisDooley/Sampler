/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveThumbnail.h"
#include "ADSRComponent.h"

//==============================================================================
/**
*/
class SamplerAudioProcessorEditor : public juce::AudioProcessorEditor,
                                public juce::Timer
{
public:
    SamplerAudioProcessorEditor (SamplerAudioProcessor&);
    ~SamplerAudioProcessorEditor();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override;
    
private:    
    WaveThumbnail mWaveThumbnail;
    ADSRComponent mADSR;
    juce::ImageComponent mImageComponent;
    
    SamplerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerAudioProcessorEditor)
};
