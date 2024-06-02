/*
  ==============================================================================

    WaveThumbnail.h
    Created: 1 Jun 2024 4:52:53pm
    Author:  Marquis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/*
*/
class WaveThumbnail  : public juce::Component,
                     public juce::FileDragAndDropTarget
{
public:
    WaveThumbnail(SamplerAudioProcessor& p);
    ~WaveThumbnail();

    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped (const juce::StringArray& files, int x, int y) override;

private:
    std::vector<float> mAudioPoints;
    bool mShouldBePainting { false };
    
    juce::String mFileName {""};
    
    SamplerAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveThumbnail)
};
