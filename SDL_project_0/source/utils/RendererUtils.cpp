#include "stdafx.h"
#include "RendererUtils.h"
#include "RenderableObject.h"
#include "Collider.h"

bool DrawCallComparator::operator()( DrawCall& lho, DrawCall& rho) const {
    return lho.renderElement->GetSortingPriority() < rho.renderElement->GetSortingPriority();
}

//bool ColliderComparator::operator()(Collider* lhc, Collider* rhc) const
//{
//    return lhc->GetOwnerId() < rhc->GetOwnerId();
//}

DrawCall::DrawCall(Renderable* rEl, Transform wTrans) :
	renderElement(rEl),
	rotation(wTrans.rotation),
	rect(),
	rotationPivot()
{
	Vector2d scrSize = (Vector2i)renderElement->GetSize();
	rect.x = int(wTrans.position.x - (double(scrSize.x) * wTrans.pivot.x * wTrans.scale.x));
	rect.y = int(wTrans.position.y - (double(scrSize.y) * wTrans.pivot.y * wTrans.scale.y));
	rect.w = (int)(scrSize.x * wTrans.scale.x);
	rect.h = (int)(scrSize.y * wTrans.scale.y);
	rotationPivot.x = int((float)rect.w * wTrans.pivot.x);
	rotationPivot.y = int((float)rect.h * wTrans.pivot.y);
}
