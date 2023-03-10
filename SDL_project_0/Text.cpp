#include "stdafx.h"
#include "Text.h"
#include "AssetManager.h"
#include "EntityManager.h"

Text::Text(uint32_t iD, std::string n, Transform t, Vector2i s, shared_Texture tex, CoreFont::ECoreFont ft, std::string txt, SDL_Color col) :
	RenderObject(iD, n, t, s, tex),
	font(ft),
	text(txt),
	color(col)
{
	bUpdate = false;
}

Text::Text() : RenderObject(
	EntityManager::Get()->GetFreeEntityID(), 
	((std::string)typeid(this).name()).append("_" + std::to_string(EntityManager::Get()->GetFreeEntityID())), 
	Transform(),
	Vector2i::zero,
	nullptr),
	text(""),
	color(SDL_Color()),
	font(CoreFont::CALIBRI)
{
	bUpdate = false;
}

void Text::UpdateText()
{
	if (text == "") text = std::string("text_").append(std::to_string(id));
	shared_Texture newTexture = AssetManager::Get()->MakeTextureFromText(font, text.c_str(), color);
	SDL_QueryTexture(newTexture.get(), NULL, NULL, &screenSize.x, &screenSize.y);

	texture = newTexture;
	//AssetManager::Get()->SetTextureLock(texture, false);
}

Text& Text::SetAndUpdateText(std::string txt)
{
	if (txt != text) {
		text = txt;
		UpdateText();
	}
	return *this;
}
