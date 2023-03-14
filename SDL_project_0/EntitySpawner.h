#pragma once
#include "CoreFonts.h"
#include "EntityManager.h"

class Text;
class Actor;

struct ActorSpawnData {
    const Vector2i& size;
    EntityManager& eManager;

    ActorSpawnData(const Vector2i inSize, EntityManager& inEManager);
};

class EntitySpawner
{
private:
    
    static ActorSpawnData GetActorSpawnData(shared_Texture tex, const Vector2i& s, std::string n);
    static ActorSpawnData GetTextSpawnData(const Vector2i& s, std::string txt, CoreFont::ECoreFont font, SDL_Color col);
public:

    //ActorSpawners----------------------------------------------------
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<Actor, T>>
    >
    static std::weak_ptr<T> SpawnActor(Transform& t, shared_Texture tex = nullptr, const Vector2i& s = Vector2i::zero, std::string n = "") 
    {
        ActorSpawnData data = GetActorSpawnData(tex, s, n);
        Vector2i size = data.size; //whatthefuck.png
        auto actor = data.eManager.AddEntity<T>(std::make_shared<T>()).lock();
        if (n != "") actor->name = n;
        if (t != Transform()) actor->SetTransform(t);
        if (size != Vector2i::zero) actor->SetScreenSize(size);
        if (tex != nullptr) actor->SetTexture(tex);
        actor->Begin();
        return actor;
    }
    
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<Actor, T>>
    >
    static std::weak_ptr<T> SpawnActor(Transform&& t = Transform(), shared_Texture tex = nullptr, const Vector2i& s = Vector2i::zero, std::string n = "") 
    {
        return SpawnActor<T>(t, tex, s, n);
    }
    
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<Actor, T>>
    >
    static std::weak_ptr<T> SpawnActor(const Vector2i& p, shared_Texture tex = nullptr, const Vector2i& s = Vector2i::zero, std::string n = "")
    {
        return SpawnActor<T>(Transform(p), tex, s, n);
    }
    //ActorSpawners----------------------------------------------------
    
    //static std::weak_ptr<Actor> SpawnActor(const Vector2i& p = Vector2i::zero, const Vector2i& s = Vector2i::zero, shared_Texture tex = nullptr, std::string n = "");

    //TextSpawners----------------------------------------------------
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
    //TextSpawners----------------------------------------------------
};

