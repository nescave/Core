#pragma once

class Animation
{
private:
    double time;
    bool bPaused;
public:
    Vector2i spriteSlices;
    uint16_t startFrame;
    uint16_t endFrame;
    uint16_t currentFrame;
    uint16_t fps;
    bool bLooping;
    bool bReverse;

    Animation();
    Animation(
        uint16_t _spriteRows,
        uint16_t _spriteColumns,
        uint16_t _startFrame,
        uint16_t _endFrame,
        uint16_t _fps,
        bool _bLooping,
        bool _bReverse
        // Vector2d _frameSize,
    );

    void Play();
    void Pause();
    void Stop();
    void Update(double dTime);
    bool IsPlaying() const {return !bPaused;}
};
