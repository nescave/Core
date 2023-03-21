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
	Vector2i scrSize = (Vector2i)renderElement->GetSize();
	rect.x = int(wTrans.position.x - (double(scrSize.x) / 2 * wTrans.scale.x));
	rect.y = int(wTrans.position.y - (double(scrSize.y) / 2 * wTrans.scale.y));
	rect.w = (uint32_t)(double(scrSize.x) * wTrans.scale.x);
	rect.h = (uint32_t)(double(scrSize.y) * wTrans.scale.y);
	rotationPivot.x = rect.w / 2;
	rotationPivot.y = rect.h / 2;
}
