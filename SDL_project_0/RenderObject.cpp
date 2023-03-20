#include "stdafx.h"
#include "RenderObject.h"

RenderObject::RenderObject()
{}

Renderable& RenderObject::SetScreenSize(Vector2i s, bool resetScale)
{
	if (resetScale) transform.scale = Vector2f::one;
	Renderable::SetScreenSize(s, false);
	return *this;
}

Vector2i RenderObject::GetAnchorOffset(Anchor anch)
{
	Vector2i scaledScSize = screenSize * transform.scale;
		switch (anch){
		case Anchor::TopLeft:
			return Vector2i(-scaledScSize.x / 2, -scaledScSize.y / 2);;
		case Anchor::Top:
			return Vector2i(0, -scaledScSize.y / 2);
		case Anchor::TopRight:
			return Vector2i(scaledScSize.x / 2, -scaledScSize.y / 2);
		case Anchor::Left:
			return Vector2i(-scaledScSize.x / 2, 0);
		case Anchor::Center:
			return Vector2i::zero;
		case Anchor::Right:
			return Vector2i(scaledScSize.x / 2, 0);
		case Anchor::BottomLeft:
			return Vector2i(-scaledScSize.x / 2, scaledScSize.y / 2);
		case Anchor::Bottom:
			return Vector2i(0, scaledScSize.y / 2);
		case Anchor::BottomRight:
			return Vector2i(scaledScSize.x / 2, scaledScSize.y / 2);;
		default:
			break;
		}
	return Vector2i();
}
