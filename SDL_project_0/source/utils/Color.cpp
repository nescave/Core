#include "stdafx.h"
#include "Color.h"

Color::Color(uint8_t x, uint8_t y, uint8_t z, uint8_t w) :
r(x),
g(y),
b(z),
a(w)
{}

Color::Color() :
r(0),
g(0),
b(0),
a(0)
{}

const Color Color::red = {255,0,0,255};
const Color Color::green = {0,255,0,255};
const Color Color::blue = {0,0,255,255};
const Color Color::yellow = {255,255,0,255};
const Color Color::purple = {255,0,255,255};
const Color Color::cyan = {0,255,255,255};
const Color Color::white = {255,255,255,255};
const Color Color::black = {0,0,0,255};
