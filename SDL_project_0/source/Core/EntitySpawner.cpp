#include "stdafx.h"
#include "EntitySpawner.h"
#include "Actor.h"
#include "Text.h"
#include "Core.h"
#include "AssetManager.h"
#include "CoreFunctions.h"

EntityManager& EntitySpawner::GetEntityManager()
{
	return Core::Get().GetEntityManager();
}

//std::weak_ptr<Text> EntitySpawner::SpawnText(Transform& t, const Vector2i& s, std::string n, std::string txt, CoreFont::ECoreFont font, SDL_Color col)
//{
//	auto text = GetEntityManager().AddEntity<Text>(std::make_shared<Text>()).lock();
//	text->SetColor(col);
//	text->SetFont(font);
//	if (n != "") text->name = n;
//	if (t != Transform()) text->SetTransform(t);
//	text->SetAndUpdateText(txt);
//	if (s != Vector2i::zero) text->SetScreenSize(s);
//	return text;
//}

