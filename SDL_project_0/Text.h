#pragma once
#include "RenderObject.h"
#include "CoreFonts.h"

class Text :
    public RenderObject
{
private:
    
    CoreFont::ECoreFont font;
    std::string text;
    SDL_Color color;
    void UpdateText();

public:
    Text(
        uint32_t iD,
        std::string n, 
        Transform t, 
        Vector2i s, 
        shared_Texture tex, 
        CoreFont::ECoreFont ft = CoreFont::CALIBRI, 
        std::string txt = "baka", 
        SDL_Color col = {255,255,255}
    );

    Text();

    bool ShouldRender() override { return texture.get(); }

    std::string GetText() { return text; }

    Text& SetAndUpdateText(std::string txt);
    Text& SetColor(SDL_Color col) { color = col; return *this; }
    Text& SetFont(CoreFont::ECoreFont fnt) { font = fnt; return *this; }
};

