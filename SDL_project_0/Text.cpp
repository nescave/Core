#include "stdafx.h"
#include "Text.h"
#include "AssetManager.h"
#include "EntityManager.h"

Text::Text(weak_Object own, std::string txt, SDL_Color col, CoreFont::ECoreFont ft) : 
	RenderableComponent(own),
	font(ft),
	text(txt),
	color(col)
{}

Text::Text(weak_Object own) : 
	Text(own, "", { 255,255,255,0 }, CoreFont::CALIBRI)
{

}

void Text::UpdateText()
{
	texture = GetTextureFromText();
	SetScreenSize(GetSizeFromTexture(texture));
	//AssetManager::Get()->SetTextureLock(texture, false);
}

shared_Texture Text::GetTextureFromText()
{
	return AssetManager::Get()->MakeTextureFromText(font, text.c_str(), color);
}

Text& Text::SetAndUpdateText(std::string txt)
{
	if (txt != text) {
		text = txt;
		UpdateText();
	}
	if (text == "") text = owner.lock()->name.append("_text");
	return *this;
}
