#include "stdafx.h"
#include "RendererUtils.h"
#include "RenderableObject.h"
#include "Collider.h"

bool DrawCallComparator::operator()( DrawCall& lho, DrawCall& rho) const {
    return lho.sortingPriority < rho.sortingPriority;
}

//bool ColliderComparator::operator()(Collider* lhc, Collider* rhc) const
//{
//    return lhc->GetOwnerId() < rhc->GetOwnerId();
//}

DrawCall::DrawCall(Renderable* rEl, Transform wTrans) :
	texture(&*rEl->GetTexture()),
	sortingPriority(rEl->GetSortingPriority()),
	rotation(wTrans.rotation),
	srcRect(),
	dstRect(),
	rotationPivot()
{
	// Vector2d scrSize = (Vector2i)rEl->GetSize();
	srcRect = rEl->GetSrcRect();
	dstRect = rEl->GetDstRect();
	
	rotationPivot.x = int((float)dstRect.w * wTrans.pivot.x);
	rotationPivot.y = int((float)dstRect.h * wTrans.pivot.y);
}
