#include "stdafx.h"
#include "RendererUtils.h"
#include "RenderableObject.h"
#include "Collider.h"


//bool ColliderComparator::operator()(Collider* lhc, Collider* rhc) const
//{
//    return lhc->GetOwnerId() < rhc->GetOwnerId();
//}

DrawCall::DrawCall(Renderable* rEl, Transform wTrans) :
	texture(&*rEl->GetTexture()),
	sortingPriority(rEl->GetSortingPriority()),
	rotation(wTrans.rotation),
	size(rEl->GetSize()),
	srcRect(rEl->GetSrcRect()),
	wTransform(wTrans),
	rotationPivot()
{
	// Vector2d scrSize = (Vector2i)rEl->GetSize();
	
	rotationPivot.x = int((float)rEl->GetSize().x * wTrans.scale.x * wTrans.pivot.x);
	rotationPivot.y = int((float)rEl->GetSize().y * wTrans.scale.y * wTrans.pivot.y);
}

bool DrawCallComparator::operator()( DrawCall& lho, DrawCall& rho) const {
    return lho.sortingPriority < rho.sortingPriority;
}
