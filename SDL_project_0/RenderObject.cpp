#include "stdafx.h"
#include "RenderObject.h"

RenderObject::RenderObject(int iD, std::string n, Transform t, Vector2i s, shared_Texture tx) :
	Object(iD, n, t),
	screenSize(s),
	texture(tx),
	sortingPriority((int)ESortingPriority::AVERAGE),
	blendMode(SDL_BLENDMODE_BLEND)
{
	UpdateRect();
}

void RenderObject::UpdateRect() {
	auto transf = GetUnifiedTransform();
	rect.x = transf.position.x;
	rect.y = transf.position.y;
	rect.w = (int)(transf.scale.x * screenSize.x);
	rect.h = (int)(transf.scale.y * screenSize.y);
}


RenderObject& RenderObject::SetBlendMode(SDL_BlendMode mode) {
	blendMode = mode;
	if (texture) {
		SDL_SetTextureBlendMode(texture.get(), blendMode);
	}
	return *this;
}
RenderObject& RenderObject::SetSortingPriority(ESortingPriority priority, int offset ) {
	sortingPriority = (int)priority + offset;
	return *this;
}
