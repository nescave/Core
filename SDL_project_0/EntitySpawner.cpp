#include "stdafx.h"
#include "EntitySpawner.h"
#include "Actor.h"
#include "Text.h"
#include "Core.h"
#include "AssetManager.h"
#include "EntityManager.h"
#include "CoreFunctions.h"

std::weak_ptr<Actor> EntitySpawner::SpawnActor(Transform& t, const Vector2i& s, shared_Texture tex, std::string n) {
    auto& core = Core::Get();
    auto& eManager = core.GetEntityManager();
    int freeId = GetFirstFreeID(eManager.gameEntities);
    if (n == "") n = std::string("object_").append(std::to_string(freeId));
    if (s == Vector2i::zero && tex != nullptr) {
        int w, h;
        SDL_QueryTexture(&*tex, NULL, NULL, &w, &h);
        return eManager.AddEntity<Actor>(std::make_shared<Actor>(freeId, n, t, Vector2i(w, h), tex));
    }
    return eManager.AddEntity<Actor>(std::make_shared<Actor>(freeId, n, t, s, tex));
}
std::weak_ptr<Actor> EntitySpawner::SpawnActor(Transform&& t, const Vector2i& s, shared_Texture tex, std::string n) {
    return SpawnActor(t, s, tex, n);
}
std::weak_ptr<Actor> EntitySpawner::SpawnActor(const Vector2i& p, const Vector2i& s, shared_Texture tex, std::string n)
{
    return SpawnActor(Transform(p), s, tex, n);
}

std::weak_ptr<Text> EntitySpawner::SpawnText(Transform& t, const Vector2i& s, std::string n, std::string txt, CoreFont::ECoreFont font, SDL_Color col) {
    auto& core = Core::Get();
    auto& eManager = core.GetEntityManager();
    int freeId = GetFirstFreeID(eManager.gameEntities);
    if (n == "") n = std::string("text_").append(std::to_string(freeId));
    shared_Texture texture = AssetManager::Get()->MakeTextureFromText(font, txt.c_str(), col);
    if (s == Vector2i::zero) {
        int w, h;
        SDL_QueryTexture(&*texture, NULL, NULL, &w, &h);
        return eManager.AddEntity<Text>(std::make_shared<Text>(freeId, n, t, Vector2i(w, h), texture));
    }

    return eManager.AddEntity<Text>(std::make_shared<Text>(freeId, n, t, s, texture));
}
std::weak_ptr<Text> EntitySpawner::SpawnText(Transform&& t, const Vector2i& s, std::string n, std::string txt, CoreFont::ECoreFont font, SDL_Color col)
{
    return SpawnText(t, s, n, txt, font, col);
}
std::weak_ptr<Text> EntitySpawner::SpawnText(const Vector2i& p, const Vector2i& s, std::string n, std::string txt, CoreFont::ECoreFont font, SDL_Color col)
{
    return SpawnText(Transform(p), s, n, txt, font, col);
}
