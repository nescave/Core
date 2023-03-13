#include "stdafx.h"
#include "RenderObject.h"

RenderObject::RenderObject(uint32_t iD, std::string n, Transform t, Vector2i s, shared_Texture tx) :
	Object(iD, n, t),
	screenSize(s),
	texture(tx),
	sortingPriority((uint16_t)ESortingPriority::AVERAGE),
	blendMode(SDL_BLENDMODE_BLEND)
{
	UpdateRect();
}

void RenderObject::UpdateRect() {
	auto transf = GetUnifiedTransform();
	rect.x = transf.position.x;
	rect.y = transf.position.y;
	rect.w = (uint32_t)(transf.scale.x * screenSize.x);
	rect.h = (uint32_t)(transf.scale.y * screenSize.y);
}


RenderObject& RenderObject::SetBlendMode(SDL_BlendMode mode) {
	blendMode = mode;
	if (texture) {
		SDL_SetTextureBlendMode(texture.get(), blendMode);
	}
	return *this;
}
RenderObject& RenderObject::SetSortingPriority(ESortingPriority priority, int_fast16_t offset ) {
	sortingPriority = (int_fast16_t)priority + offset;
	return *this;
}
