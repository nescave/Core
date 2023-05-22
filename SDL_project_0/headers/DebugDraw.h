#pragma once
#include "CoreTypes.h"
#include "Color.h"

class DebugDraw
{
    static std::set<SharedSceneObject> sketches;
public:
    static void Point(
        const Vector2d& point,
        double size,
        double time = -1, Color color = Color::red
    );
    static void Line(
        const Vector2d& firstPoint,
        const Vector2d& secondPoint,
        double thickness,
        double time = -1, Color color = Color::red
    );
    static void Circle(
        const Vector2d& center,
        float radius, double time = -1,
        Color color = Color::red
        );
    static void CleanSketches();
};
