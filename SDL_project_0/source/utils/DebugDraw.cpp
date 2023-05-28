#include "stdafx.h"
#include "DebugDraw.h"

#include "AssetManager.h"
#include "CoreTextures.h"
#include "ObjectSpawner.h"
#include "CoreTypes.h"
#include "RenderableObject.h"

std::set<SharedSceneObject> DebugDraw::sketches = std::set<SharedSceneObject>();

void DebugDraw::Point(const Vector2d& point, double size, double time, Color color)
{
    const SharedTexture tempTexture = AssetManager::Get()->LoadTexture("../SDL_project_0/res/pngs/white_dot.png");

    if(!tempTexture) return;
    SDL_SetTextureColorMod(&*tempTexture, color.r, color.g, color.b);
    
    const SharedRenderableObject sketch = ObjectSpawner::SpawnObject<RenderableObject>(
        point,
        tempTexture,
        Vector2d(size,size),
        std::string("debugPoint")
        );

    sketch->SetSortingPriority(ESortingPriority::HIGHEST);
    
    if(time>0)
        sketch->Destroy(time);
    else
        sketches.insert(sketch);
}
//
// void DebugDraw::Point(Vector2d&& point, double size, double time, Color color)
// {
//     Point(point, size, time, color);
// }

void DebugDraw::Line(const Vector2d& firstPoint, const Vector2d& secondPoint, double thickness, double time, Color color)
{
    const SharedTexture tempTexture = AssetManager::Get()->CreateFlatTexture(64,64, color);

    if(!tempTexture) return;
    // SDL_SetTextureColorMod(&*tempTexture, color.r, color.g, color.b);
    const SharedRenderableObject sketch = ObjectSpawner::SpawnObject<RenderableObject>(
        Transform(firstPoint, 0, {1,1}, {.5,1}),
        tempTexture,
        Vector2d(thickness,Vector2d::Distance(firstPoint, secondPoint)),
        std::string("debugLine")
        );

    sketch->SetSortingPriority(ESortingPriority::HIGHEST);
    sketch->SetRotation(sketch->GetLookAtRotation(secondPoint));

    if(time>0)
        sketch->Destroy(time);
    else
        sketches.insert(sketch);
}

void DebugDraw::Circle(const Vector2d& center, float radius, double time, Color color)
{
    const SharedTexture tempTexture = AssetManager::Get()->LoadTexture("../SDL_project_0/res/pngs/circle.png");

    if(!tempTexture) return;
    SDL_SetTextureColorMod(&*tempTexture, color.r, color.g, color.b);

    const SharedRenderableObject sketch = ObjectSpawner::SpawnObject<RenderableObject>(
        Transform(center, 0, {1,1}, {.5,.5}),
        tempTexture,
        Vector2d(radius,radius)*2,
        std::string("debugCircle")
        );

    sketch->SetSortingPriority(ESortingPriority::HIGHEST);

    if(time>0)
        sketch->Destroy(time);
    else
        sketches.insert(sketch);
}

void DebugDraw::CleanSketches()
{
    for(auto sketch : sketches)
    {
        sketch->Destroy();
    }
    sketches.clear();
}
