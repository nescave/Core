#pragma once
#include "CoreTypes.h"
#include "CoreFonts.h"
class Actor;
class Text;

class EntitySpawner
{
public:
    static std::weak_ptr<Actor> SpawnActor(Transform& t, const Vector2i& s = Vector2i::zero, shared_Texture tex = nullptr, std::string n = "");
    static std::weak_ptr<Actor> SpawnActor(Transform&& t = Transform(), const Vector2i& s = Vector2i::zero, shared_Texture tex = nullptr, std::string n = "");
    static std::weak_ptr<Actor> SpawnActor(const Vector2i& p, const Vector2i& s = Vector2i::zero, shared_Texture tex = nullptr, std::string n = "");
    
    static std::weak_ptr<Text> SpawnText(
        Transform& t,
        const Vector2i& s = Vector2i::zero,
        std::string n = "",
        std::string txt = "Text",
        CoreFont::ECoreFont font = CoreFont::CALIBRI,
        SDL_Color col = { 255,255,255 }
    );
    static std::weak_ptr<Text> SpawnText(
        Transform&& t = Transform(),
        const Vector2i& s = Vector2i::zero,
        std::string n = "",
        std::string txt = "Text",
        CoreFont::ECoreFont font = CoreFont::CALIBRI,
        SDL_Color col = { 255,255,255 }
    );
    static std::weak_ptr<Text> SpawnText(
        const Vector2i& p,
        const Vector2i& s = Vector2i::zero,
        std::string n = "",
        std::string txt = "Text",
        CoreFont::ECoreFont font = CoreFont::CALIBRI,
        SDL_Color col = { 255,255,255 }
    );
};

