#include "stdafx.h"
#include "Renderable.h"

Renderable::Renderable() :
	texture(nullptr),
	size(Vector2d::zero),
	blendMode(SDL_BLENDMODE_BLEND),
	sortingPriority((uint16_t)ESortingPriority::AVERAGE)
{}

Vector2i Renderable::GetSizeFromTexture(SharedTexture tex)
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

Renderable& Renderable::SetTexture(SharedTexture tx)
{
	// if (!tx) return *this;
	texture = tx;
	if (size == Vector2d::zero) SetSize(GetSizeFromTexture(tx), true);
	return *this;
}


Renderable& Renderable::SetSize(Vector2d s, bool)
{
	size = s;
	return *this;
}
