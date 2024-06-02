/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplerAudioProcessorEditor::SamplerAudioProcessorEditor (SamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), mWaveThumbnail(p), mADSR(p), processor (p)
{
    auto image = juce::ImageCache::getFromMemory(BinaryData::Plugin_Logo_png, BinaryData::Plugin_Logo_pngSize);
    
    if (!image.isNull())
        mImageComponent.setImage(image, juce::RectanglePlacement::onlyReduceInSize);
    else
        jassert(!image.isNull());
    
    addAndMakeVisible(mWaveThumbnail);
    addAndMakeVisible(mADSR);
    addAndMakeVisible(mImageComponent);
    
    startTimerHz(30);
    
    setSize (600, 400);
}

SamplerAudioProcessorEditor::~SamplerAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void SamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void SamplerAudioProcessorEditor::resized()
{
    mWaveThumbnail.setBoundsRelative(0.0, 0.25, 1.0, 0.5);
    mADSR.setBoundsRelative(0.0f, 0.75f, 1.0f, 0.25f);
    mImageComponent.setBoundsRelative(0.0f, 0.0f, 0.35f, 0.25f);
}

void SamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}


