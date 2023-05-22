#pragma once
#include "RenderableObject.h"
class BaseGUI :
    public RenderableObject
{
public:
    BaseGUI();
    void OnSpawn() override;
    void Update(double dTime) override;
};
