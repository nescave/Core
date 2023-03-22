#include "stdafx.h"
#include "Avatar.h"
#include "InputManager.h"

Avatar::Avatar() :
    input(nullptr),
    bActive(true)
{
    input = InputManager::Get();
}

void Avatar::RegisterAction(ECoreActionButton but, const std::function<void()>& f, const EActionType type) const
{
    input->RegisterAction(but, [f, this](){if(this->bActive) f();}, type);
}

void Avatar::OnSpawn()
{
    Actor::OnSpawn();
}

void Avatar::Begin()
{
    Actor::Begin();
}

void Avatar::Update(double dTime)
{
    Actor::Update(dTime);
    // if(!bActive) return;
}
