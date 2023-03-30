#pragma once

struct Color
{
    uint8_t r, g, b, a;

    static const Color red;
    static const Color green;
    static const Color blue;
    static const Color yellow;
    static const Color purple;
    static const Color cyan;
    static const Color white;
    static const Color black;

    Color(uint8_t x, uint8_t y, uint8_t z, uint8_t w);
    Color();
    operator SDL_Color() const
    {
        return {r,g,b,a};
    }
};
