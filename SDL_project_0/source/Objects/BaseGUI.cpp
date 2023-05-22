#include "stdafx.h"
#include "BaseGUI.h"

BaseGUI::BaseGUI() : RenderableObject()
{
	
}

void BaseGUI::OnSpawn()
{
	RenderableObject::OnSpawn();
}

void BaseGUI::Update(double dTime)
{
	RenderableObject::Update(dTime);
}
