#include "stdafx.h"
#include "Renderable.h"

Renderable::Renderable(shared_Texture tx, const Vector2i s) :
	texture(tx),
	screenSize(s),
	sortingPriority((uint16_t)ESortingPriority::AVERAGE),
	blendMode(SDL_BLENDMODE_BLEND)
{}

Renderable::Renderable(shared_Texture tx) :
	Renderable(tx, GetSizeFromTexture(tx))
{}

Renderable::Renderable() :
	Renderable(nullptr)
{}

const Vector2i Renderable::GetSizeFromTexture(shared_Texture tex)
{
	if (!tex) return Vector2i::zero;
	Vector2i vec;
	SDL_QueryTexture(&*texture, 0, 0, &vec.x, &vec.y);
	return vec;
}

Renderable& Renderable::SetSortingPriority(ESortingPriority priority, int_fast16_t offset)
{
	sortingPriority = (int_fast16_t)priority + offset;
	return *this;
}

Renderable& Renderable::SetBlendMode(SDL_BlendMode mode)
{
	blendMode = mode;
	if (texture) {
		SDL_SetTextureBlendMode(texture.get(), blendMode);
	}
	return *this;
}

Renderable& Renderable::SetTexture(shared_Texture tx)
{
	if (!tx) return *this;
	texture = tx;
	if (screenSize == Vector2i::zero) SetScreenSize(GetSizeFromTexture(tx), true);
	return *this;
}


Renderable& Renderable::SetScreenSize(Vector2i s, bool)
{
	screenSize = s;
	return *this;
}
