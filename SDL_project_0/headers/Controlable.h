#pragma once
#include "CoreActionButtons.h"
#include "InputManager.h"

class InputManager;

class Controlable //TODO it would be nice to make this an abstract class
{
    friend class ObjectSpawner;
private:
    InputManager* input;
    bool bActive;       //use to temporarily deactivate input based functions
    
public:
    Controlable();

    void RegisterAction(ECoreActionButton but, const std::function<void()>& f, const EActionType = EActionType::SINGLE) const;
    bool IsActive() const{return bActive;}
    void SetActive(bool state){bActive = state;}
    
};
