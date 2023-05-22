#pragma once
#include "BaseGUI.h"
#include "Color.h"

class Text;

class FloatingTextUI : public BaseGUI
{
    friend class ObjectSpawner;
protected:
    std::string text;
    Text* textComponent;
    Color color;
    FloatingTextUI();
public:
    float floatSpeed;
    float reportedDamage;
    FloatingTextUI& SetText(std::string txt);    
    FloatingTextUI& SetColor(Color col);    

    void OnSpawn() override;
    void Update(double dTime) override;
};
