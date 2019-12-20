/*
  ==============================================================================

    ItemDataStruct.h
    Created: 14 Dec 2019 8:29:36pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

struct ItemInfo
{
    int itemIndex;
    File* file;
    int64_t size;
    int64_t lengthInSamples;
    double sampleRate;
    int numChannels;
    int lengthInSecs;
    String lengthInTime;
    bool Loop;
    int numLoops;
};
