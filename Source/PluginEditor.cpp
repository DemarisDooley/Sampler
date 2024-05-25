/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplerAudioProcessorEditor::SamplerAudioProcessorEditor (SamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    mLoadButton.onClick = [&]() { processor.loadFile(); };
    addAndMakeVisible(mLoadButton);
    
    setSize (600, 200);
}

SamplerAudioProcessorEditor::~SamplerAudioProcessorEditor()
{
}

//==============================================================================
void SamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    
    g.setColour(juce::Colours::white);
    
    // if new file dropped...
    if (mShouldBePainting)
    {
        juce::Path p;
        mAudioPoints.clear();
        
        // get the wave form from the processor
        auto waveform = processor.getWaveForm();
        
        // find ratio: sample = 44100 (1 sec)... x axis of window  = 600 == sampleLength / getWidth()
        auto ratio = waveform.getNumSamples() / getWidth();
        
        // values of audiofile -1 and 1... y axis of window is 200... -1 to 1 in audio to mean 200 to 0
        // use the ratio to take values from the audio buffer and put in vector to display
        auto buffer = waveform.getReadPointer(0);
        // scale audio file to window on x axis
        for (int sample = 0; sample < waveform.getNumSamples(); sample+=ratio)
        {
            mAudioPoints.push_back(buffer[sample]);
        }
        
        p.startNewSubPath(0, getHeight() / 2);
        
        // scale on y axis
        for(int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            auto point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, 200, 0);
            p.lineTo(sample, point);
        }
        
        // draw the waveform
        g.strokePath(p, juce::PathStrokeType(2));
        
        mShouldBePainting = false;
    }
//    g.setColour(juce::Colours::white);
//    g.setFont(15.0f);
//    
//    if (processor.getNumSamplerSounds() > 0)
//    {
//        g.fillAll(juce::Colours::green);
//        g.drawText("Sound Loaded", getWidth() / 2 - 50, getHeight() / 2 - 10, 100, 20, juce::Justification::centred);
//    }
//    else
//    {
//        g.drawText("Load a Sound", getWidth() / 2 - 50, getHeight() / 2 - 10, 100, 20, juce::Justification::centred);
//    }
}

void SamplerAudioProcessorEditor::resized()
{
    //mLoadButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);
}

bool SamplerAudioProcessorEditor::isInterestedInFileDrag(const juce::StringArray &files)
{
    for (auto file : files) {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif"))
        {
            return true;
        }
    }
    
    return false;
}

void SamplerAudioProcessorEditor::filesDropped(const juce::StringArray& files, int x, int y)
{
    for (auto file : files) 
    {
        if (isInterestedInFileDrag(file))
        {
            mShouldBePainting = true;
            processor.loadFile(file);
        }
    }
    repaint();
}
