#include "stdafx.h"
#include "Animation.h"

Animation::Animation() : Animation(1,1,0,0,12,false,false)
{}

Animation::Animation(
    uint16_t _spriteRows,
    uint16_t _spriteColumns,
    uint16_t _startFrame,
    uint16_t _endFrame,
    uint16_t _fps,
    bool _bLooping,
    bool _bReverse
) :
    time(0),
    bPaused(false),
    spriteSlices({_spriteColumns, _spriteRows}),
    // spriteRows(_spriteRows),
    // spriteColumns(_spriteColumns),
    startFrame(_startFrame),
    endFrame(_endFrame),
    currentFrame(_startFrame),
    fps(_fps),
    bLooping(_bLooping),
    bReverse(_bReverse)
{}

void Animation::Play()
{
    bPaused = false;
}

void Animation::Pause()
{
    bPaused = true;
}

void Animation::Stop()
{
    bPaused = true;
    time = 0;
    currentFrame = startFrame;
}

void Animation::Update(double dTime)
{
    if(bPaused) return;
    
    time += dTime;
    if(time>1.0/(double)fps)
    {
        if(!bReverse)
        {
            if(++currentFrame >= endFrame)
            {
                if(bLooping)
                    currentFrame = startFrame;
                else
                    Pause();
            }
        }else
        {
            if(--currentFrame <=startFrame)
            {
                if (bLooping)
                    currentFrame = endFrame;
                else
                    Pause();
            }
        }
        time -=1.0/(double)fps;
    }
}
