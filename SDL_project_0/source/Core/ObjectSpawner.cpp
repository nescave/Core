#include "stdafx.h"
#include "ObjectSpawner.h"
#include "Actor.h"
#include "Text.h"
#include "Core.h"
#include "AssetManager.h"
#include "CoreFunctions.h"

ObjectManager& ObjectSpawner::GetObjectManager()
{
	return Core::Get().GetObjectManager();
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

