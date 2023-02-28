#include "stdafx.h"
#include "RendererUtils.h"
#include "RenderObject.h"
#include "Collider.h"

bool RenderObjectComparator::operator()( RenderObject* lho,  RenderObject* rho) const {
    return lho->GetSortingPriority() < rho->GetSortingPriority();
}

//bool ColliderComparator::operator()(Collider* lhc, Collider* rhc) const
//{
//    return lhc->GetOwnerId() < rhc->GetOwnerId();
//}
