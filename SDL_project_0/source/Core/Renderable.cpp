#include "stdafx.h"
#include "Renderable.h"


Renderable::Renderable() :
	texture(nullptr),
	size(Vector2d::zero),
	blendMode(SDL_BLENDMODE_BLEND),
	sortingPriority((uint16_t)ESortingPriority::AVERAGE)
{}

Vector2d Renderable::GetSize()
{
	return animation ?  Vector2d((Vector2i)size / animation->spriteSlices) : size;
}

Vector2i Renderable::GetSizeFromTexture(SharedTexture tex)
{
	if (!tex) return Vector2i::zero;
	Vector2i vec;
	SDL_QueryTexture(&*texture, 0, 0, &vec.x, &vec.y);
	return vec;
}

SDL_Rect Renderable::GetDstRect()
{
	return SDL_Rect{0,0, (int)GetSize().x, (int)GetSize().y};
}

SDL_Rect Renderable::GetSrcRect()
{
	if(animation)
	{
		return SDL_Rect {
			int(GetSize().x * fmod(animation->currentFrame, animation->spriteSlices.x)),
			int(GetSize().y * int(animation->currentFrame/animation->spriteSlices.x)),
			(int)GetSize().x,
			(int)GetSize().y
		};
	}
	auto size = GetSizeFromTexture(texture);
	return SDL_Rect{0,0, size.x, size.y};
}

Renderable& Renderable::SetSortingPriority(ESortingPriority priority, int16_t offset)
{
	sortingPriority = (int16_t)priority + offset;
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
	if (size == Vector2d::zero) SetSize(GetSizeFromTexture(tx), false);
	return *this;
}

Renderable& Renderable::SetupAnimation(
	uint16_t rows,
	uint16_t columns,
	bool looping,
	uint16_t startFr,
	uint16_t endFr,
	uint16_t fps,
	bool reverse
)
{
	if(endFr == 0) endFr = rows*columns;

	animation = std::make_unique<Animation>(
		rows,
		columns,
		startFr,
		endFr,
		fps,
		looping,
		reverse
	);
	return *this;
}

Renderable& Renderable::SetSize(Vector2d s, bool)
{
	size = s;
	return *this;
}
