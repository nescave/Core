#include "stdafx.h"
#include "Controlable.h"
#include "InputManager.h"

Controlable::Controlable() :
    input(nullptr),
    bActive(true)
{
    input = InputManager::Get();
}

void Controlable::RegisterAction(ECoreActionButton but, const std::function<void()>& f, const EActionType type) const
{
    input->RegisterAction(but, [f, this](){if(this->bActive) f();}, type);
}
