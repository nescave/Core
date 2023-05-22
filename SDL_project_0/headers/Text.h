#pragma once
#include "RenderableComponent.h"
#include "CoreFonts.h"
#include "Color.h"

class Text :
    public RenderableComponent
{
private:
    CoreFont::ECoreFont font;
    std::string text;
    Color color;
    
    void UpdateText();

public:
    Text();

    std::string GetText() { return text; }
    SharedTexture GetTextureFromText() const;

    Text& SetText(std::string txt);
    Text& SetColor(Color col); 
    Text& SetFont(CoreFont::ECoreFont fnt);

    void OnSpawn() override;
};

