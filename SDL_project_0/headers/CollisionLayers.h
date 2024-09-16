#pragma once

enum class ECollisionLayer
{
    GAME = 1,
    PLAYER = 2,
    ENEMY = 4,
    UI = 8,
#undef IGNORE
    IGNORE = 1024
};