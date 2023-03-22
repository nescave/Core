#pragma once
#include "Actor.h"
#include "CoreActionButtons.h"
#include "InputManager.h"

class InputManager;

class Avatar : public Actor
{
private:
    InputManager* input;
    bool bActive;       //use to temporarily deactivate input based functions
    
public:
    Avatar();

    void RegisterAction(ECoreActionButton but, const std::function<void()>& f, const EActionType = EActionType::SINGLE) const;
    bool IsActive() const{return bActive;}
    void SetActive(bool state){bActive = state;}
    
    void OnSpawn() override;
    void Begin() override;
    void Update(double dTime) override;
};
