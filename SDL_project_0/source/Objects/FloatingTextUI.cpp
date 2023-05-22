#include "stdafx.h"
#include "FloatingTextUI.h"

#include <utility>
#include "Text.h"

FloatingTextUI::FloatingTextUI() :
    textComponent(nullptr),
    color(Color::white),
    floatSpeed(0),
    reportedDamage()
{}

FloatingTextUI& FloatingTextUI::SetText(std::string txt)
{
    text = txt;
    textComponent->SetText(std::move(text));
    return *this;
}

FloatingTextUI& FloatingTextUI::SetColor(Color col)
{
    color = col;
    textComponent->SetColor(color);
    return *this;
}

void FloatingTextUI::OnSpawn()
{
    BaseGUI::OnSpawn();
    textComponent = &*AddComponent<Text>();
}

void FloatingTextUI::Update(double dTime)
{
    BaseGUI::Update(dTime);
    transform.position += Vector2d::up*floatSpeed*dTime;  
}
