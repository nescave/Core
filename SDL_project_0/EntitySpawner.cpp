#include "stdafx.h"
#include "EntitySpawner.h"
#include "Actor.h"
#include "Text.h"
#include "Core.h"
#include "AssetManager.h"
#include "CoreFunctions.h"

ActorSpawnData::ActorSpawnData(uint32_t inId, std::string inName, Transform& inTransform, const Vector2i inSize, shared_Texture inTex, EntityManager& inEManager) :
	id(inId),
	name(inName),
	transform(inTransform),
	size(inSize),
	texture(inTex),
	eManager(inEManager)
{}

ActorSpawnData EntitySpawner::GetActorSpawnData(Transform& t, const Vector2i& s, shared_Texture tex, std::string n)
{
	auto& core = Core::Get();
	auto& eManager = core.GetEntityManager();
	uint32_t freeId = GetFirstFreeID(eManager.gameEntities);
	if (n == "") n = std::string("object_").append(std::to_string(freeId));
	Vector2i vec = s;
	if (s == Vector2i::zero && tex != nullptr) {
		SDL_QueryTexture(&*tex, NULL, NULL, &vec.x, &vec.y);
	}
	ActorSpawnData data(freeId, n, t, vec, tex, eManager);

	return data;
}

//std::weak_ptr<Actor> EntitySpawner::SpawnActor(const Vector2i& p, const Vector2i& s, shared_Texture tex, std::string n) {
//	//ActorSpawnData data = GetActorSpawnData(Transform(p), s, tex, n);
//	auto& core = Core::Get();
//	auto& eManager = core.GetEntityManager();
//	size_t freeId = GetFirstFreeID(eManager.gameEntities);
//	if (n == "") n = std::string("object_").append(std::to_string(freeId));
//	Vector2i vec = s;
//	if (s == Vector2i::zero && tex != nullptr) {
//		SDL_QueryTexture(&*tex, NULL, NULL, &vec.x, &vec.y);
//	}
//	ActorSpawnData data = GetActorSpawnData(Transform(p), s, tex, n);
//	vec = data.size;
//	return data.eManager.AddEntity<Actor>(std::make_shared<Actor>(data.id, data.name, data.transform, vec, data.texture));
//	//return eManager.AddEntity<Actor>(std::make_shared<Actor>(freeId, n, Transform(p), s, tex));
//}

ActorSpawnData EntitySpawner::GetTextSpawnData(Transform& t, const Vector2i& s, std::string n, std::string txt, CoreFont::ECoreFont font, SDL_Color col)
{
	auto& core = Core::Get();
	auto& eManager = core.GetEntityManager();
	uint32_t freeId = GetFirstFreeID(eManager.gameEntities);
	if (n == "") n = std::string("text_").append(std::to_string(freeId));
	shared_Texture tex = AssetManager::Get()->MakeTextureFromText(font, txt.c_str(), col);
	Vector2i vec = s;
	if (s == Vector2i::zero) {
		SDL_QueryTexture(&*tex, NULL, NULL, &vec.x, &vec.y);
	}
	ActorSpawnData data(freeId, n, t, vec, tex, eManager);
	return data;
}

std::weak_ptr<Text> EntitySpawner::SpawnText(Transform& t, const Vector2i& s, std::string n, std::string txt, CoreFont::ECoreFont font, SDL_Color col) 
{
	ActorSpawnData data = GetTextSpawnData(t, s, n, txt, font, col);
	return data.eManager.AddEntity<Text>(std::make_shared<Text>(data.id, data.name, data.transform, data.size, data.texture));
}

std::weak_ptr<Text> EntitySpawner::SpawnText(Transform&& t, const Vector2i& s, std::string n, std::string txt, CoreFont::ECoreFont font, SDL_Color col)
{
	return SpawnText(t, s, n, txt, font, col);
}

std::weak_ptr<Text> EntitySpawner::SpawnText(const Vector2i& p, const Vector2i& s, std::string n, std::string txt, CoreFont::ECoreFont font, SDL_Color col)
{
	return SpawnText(Transform(p), s, n, txt, font, col);
}
