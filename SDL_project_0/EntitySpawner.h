#pragma once
#include "CoreFonts.h"
#include "EntityManager.h"

class Text;
class Actor;

struct ActorSpawnData {
    uint32_t id;
    std::string name;
    Transform& transform;
    const Vector2i& size;
    shared_Texture texture;
    EntityManager& eManager;

    ActorSpawnData(uint32_t inId, std::string inName, Transform& inTransform, const Vector2i inSize, shared_Texture inTex, EntityManager& inEManager);
};

class EntitySpawner
{
private:
    
    static ActorSpawnData GetActorSpawnData(Transform& t, const Vector2i& s, shared_Texture tex, std::string n);
    static ActorSpawnData GetTextSpawnData(Transform& t, const Vector2i& s, std::string n, std::string txt, CoreFont::ECoreFont font, SDL_Color col);
public:

    //ActorSpawners----------------------------------------------------
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<Actor, T>>
    >
    static std::weak_ptr<T> SpawnActor(Transform& t, const Vector2i& s = Vector2i::zero, shared_Texture tex = nullptr, std::string n = "") 
    {
        ActorSpawnData data = GetActorSpawnData(t, s, tex, n);
        Vector2i size = data.size; //whatthefuck.png
        return data.eManager.AddEntity<T>(std::make_shared<T>(data.id, data.name, data.transform, size, data.texture));
    }
    
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<Actor, T>>
    >
    static std::weak_ptr<T> SpawnActor(Transform&& t = Transform(), const Vector2i& s = Vector2i::zero, shared_Texture tex = nullptr, std::string n = "") 
    {
        return SpawnActor<T>(t, s, tex, n);
    }
    
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<Actor, T>>
    >
    static std::weak_ptr<T> SpawnActor(const Vector2i& p, const Vector2i& s = Vector2i::zero, shared_Texture tex = nullptr, std::string n = "")
    {
        return SpawnActor<T>(Transform(p), s, tex, n);
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

