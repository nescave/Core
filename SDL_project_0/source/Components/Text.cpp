#include "stdafx.h"
#include "Text.h"
#include "AssetManager.h"
#include "ObjectManager.h"

Text::Text() : 
	font(CoreFont::CALIBRI),
	color(Color::white)
{}

void Text::UpdateText()
{
	texture = GetTextureFromText();
	SetSize(GetSizeFromTexture(texture));
	//AssetManager::Get()->SetTextureLock(texture, false);
}

SharedTexture Text::GetTextureFromText() const
{
	return AssetManager::Get()->MakeTextureFromText(font, text.c_str(), color);
}

Text& Text::SetText(std::string txt)
{
	if (txt != text) {
		text = txt;
		UpdateText();
	}
	if (text.empty()) text = owner.lock()->name.append("_text");
	return *this;
}

Text& Text::SetColor(Color col)
{
	color = col;
	UpdateText();
	return *this;
}

Text& Text::SetFont(CoreFont::ECoreFont fnt)
{
	font = fnt;
	UpdateText();
	return *this;
}

void Text::OnSpawn()
{
	RenderableComponent::OnSpawn();
}
