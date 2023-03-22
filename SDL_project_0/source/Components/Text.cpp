#include "stdafx.h"
#include "Text.h"
#include "AssetManager.h"
#include "ObjectManager.h"

Text::Text() : 
	text(""),
	font(CoreFont::CALIBRI),
	color({ 255,255,255,0 })
{}

void Text::UpdateText()
{
	texture = GetTextureFromText();
	SetSize(GetSizeFromTexture(texture));
	//AssetManager::Get()->SetTextureLock(texture, false);
}

SharedTexture Text::GetTextureFromText()
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

void Text::OnSpawn()
{
	RenderableComponent::OnSpawn();
}
