#include "stdafx.h"
#include "RendererUtils.h"
#include "RenderObject.h"
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
	rotation(wTrans.rotation)
{
	Vector2i scrSize = renderElement->GetScreenSize();
	rect.x = wTrans.position.x - (int)(scrSize.x / 2 * wTrans.scale.x);
	rect.y = wTrans.position.y - (int)(scrSize.y / 2 * wTrans.scale.y);
	rect.w = (uint32_t)(scrSize.x * wTrans.scale.x);
	rect.h = (uint32_t)(scrSize.y * wTrans.scale.y);
	rotationPivot.x = rect.w / 2;
	rotationPivot.y = rect.h / 2;
}
