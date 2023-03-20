#pragma once
#include "RenderableComponent.h"
#include "CoreFonts.h"

class Text :
    public RenderableComponent
{
private:
    CoreFont::ECoreFont font;
    std::string text;
    SDL_Color color;
    
    void UpdateText();

public:
    Text();

    std::string GetText() { return text; }
    shared_Texture GetTextureFromText();

    Text& SetAndUpdateText(std::string txt);
    Text& SetColor(SDL_Color col) { color = col; return *this; }
    Text& SetFont(CoreFont::ECoreFont fnt) { font = fnt; return *this; }

    void OnSpawn() override;
};

