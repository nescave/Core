#include "stdafx.h"
#include "EntitySpawner.h"
#include "Actor.h"
#include "Text.h"
#include "Core.h"
#include "AssetManager.h"
#include "CoreFunctions.h"

ActorSpawnData::ActorSpawnData(const Vector2i inSize, EntityManager& inEManager) :
	size(inSize),
	eManager(inEManager)
{}

ActorSpawnData EntitySpawner::GetActorSpawnData(shared_Texture tex, const Vector2i& s, std::string n)
{
	auto& core = Core::Get();
	auto& eManager = core.GetEntityManager();
	Vector2i vec = s;
	if (s == Vector2i::zero && tex != nullptr) {
		SDL_QueryTexture(&*tex, NULL, NULL, &vec.x, &vec.y);
	}
	ActorSpawnData data(vec, eManager);

	return data;
}

ActorSpawnData EntitySpawner::GetTextSpawnData(const Vector2i& s, std::string txt, CoreFont::ECoreFont font, SDL_Color col)
{
	auto& core = Core::Get();
	auto& eManager = core.GetEntityManager();
	shared_Texture tex = AssetManager::Get()->MakeTextureFromText(font, txt.c_str(), col);
	Vector2i vec = s;
	if (s == Vector2i::zero) {
		SDL_QueryTexture(&*tex, NULL, NULL, &vec.x, &vec.y);
	}
	ActorSpawnData data(vec, eManager);
	return data;
}

std::weak_ptr<Text> EntitySpawner::SpawnText(Transform& t, const Vector2i& s, std::string n, std::string txt, CoreFont::ECoreFont font, SDL_Color col) 
{
	auto text = EntityManager::Get()->AddEntity<Text>(std::make_shared<Text>()).lock();
	text->SetColor(col);
	text->SetFont(font);
	if (n != "") text->name = n;
	if (t != Transform()) text->SetTransform(t);
	text->SetAndUpdateText(txt);
	if (s != Vector2i::zero) text->SetScreenSize(s);
	return text;
}

std::weak_ptr<Text> EntitySpawner::SpawnText(Transform&& t, const Vector2i& s, std::string n, std::string txt, CoreFont::ECoreFont font, SDL_Color col)
{
	return SpawnText(t, s, n, txt, font, col);
}

std::weak_ptr<Text> EntitySpawner::SpawnText(const Vector2i& p, const Vector2i& s, std::string n, std::string txt, CoreFont::ECoreFont font, SDL_Color col)
{
	return SpawnText(Transform(p), s, n, txt, font, col);
}
