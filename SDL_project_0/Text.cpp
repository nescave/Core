#include "stdafx.h"
#include "Text.h"
#include "AssetManager.h"


Text::Text(int iD, std::string n, Transform t, Vector2i s, shared_Texture tex, CoreFont::ECoreFont ft, std::string txt, SDL_Color col) :
	RenderObject(iD, n, t, s, tex),
	font(ft),
	text(txt),
	color(col)
{
	bUpdate = false;
}

void Text::UpdateText()
{
	if (text == "") text = std::string("text_").append(std::to_string(id));
	shared_Texture newTexture = AssetManager::Get()->MakeTextureFromText(font, text.c_str(), color);
	int w, h;
	SDL_QueryTexture(newTexture.get(), NULL, NULL, &w, &h);
	screenSize.x = w;
	screenSize.y = h;

	texture = newTexture;
	//AssetManager::Get()->SetTextureLock(texture, false);
}
