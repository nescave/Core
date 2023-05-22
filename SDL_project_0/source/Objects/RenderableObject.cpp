#include "stdafx.h"
#include "RenderableObject.h"

RenderableObject::RenderableObject()
{}

SDL_Rect RenderableObject::GetDstRect()
{
	auto wTrans = GetAbsoluteTransform();
	Vector2d scrSize = GetSize() * wTrans.scale;
	return SDL_Rect{
		int(wTrans.position.x - scrSize.x * (double)wTrans.pivot.x),
		int(wTrans.position.y - scrSize.y * (double)wTrans.pivot.y),
		int(scrSize.x),
		int(scrSize.y)
	};
}

SDL_Rect RenderableObject::GetSrcRect()
{
	return Renderable::GetSrcRect();
}

Renderable& RenderableObject::SetSize(Vector2d s, bool resetScale)
{
	if (resetScale) transform.scale = Vector2f::one;
	Renderable::SetSize(s, false);
	return *this;
}

Vector2d RenderableObject::GetAnchorOffset(Anchor anch)
{
	Vector2d scaledScSize = size * transform.scale;
	Vector2d offset = Vector2d();
	switch (anch) {
	case Anchor::TopLeft:
		offset = Vector2d(-size.x / 2, -size.y / 2);
		break;
	case Anchor::Top:
		offset = Vector2d(0, -size.y / 2);
		break;
	case Anchor::TopRight:
		offset = Vector2d(size.x / 2, -size.y / 2);
		break;
	case Anchor::Left:
		offset = Vector2d(-size.x / 2, 0);
		break;
	case Anchor::Center:
		offset = Vector2d::zero;
		break;
	case Anchor::Right:
		offset = Vector2d(size.x / 2, 0);
		break;
	case Anchor::BottomLeft:
		offset = Vector2d(-size.x / 2, size.y / 2);
		break;
	case Anchor::Bottom:
		offset = Vector2d(0, size.y / 2);
		break;
	case Anchor::BottomRight:
		offset = Vector2d(size.x / 2, size.y / 2);;
	default:
		break;
	};
	offset *= transform.scale;
	return offset.Rotate(transform.rotation);
}

void RenderableObject::OnSpawn()
{
	SceneObject::OnSpawn();
}

void RenderableObject::Update(double dTime)
{
	SceneObject::Update(dTime);
	if(animation)
	{
		animation->Update(dTime);
	}
}
