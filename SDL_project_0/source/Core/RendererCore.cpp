#include "stdafx.h"
#include "RendererCore.h"
#include "RenderableObject.h"
#include "RenderableComponent.h"
//#include "Core.h"
#include "AssetManager.h"

RendererCore::RendererCore() :
    window(NULL),
    renderer(NULL),
    screen(NULL)
{}

bool RendererCore::Init(int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetHintWithPriority(SDL_HINT_RENDER_DRIVER, "direct3d11", SDL_HINT_OVERRIDE);

    window = SDL_CreateWindow("SDL_App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL could not create window! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL could not initialize IMG api! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    if (TTF_Init() == -1) {
        printf("SDL could not initialize TTF! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL could not initialize renderer! Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

    screen = SDL_GetWindowSurface(window);
    return true;
}

RendererCore::~RendererCore() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void RendererCore::ClearScreen() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
}
void RendererCore::UpdateScreen() {
    SDL_RenderPresent(renderer);
}

//bool RendererCore::AddRenderObjects(std::queue<RenderObject*> rObjs) {
//    while (rObjs.size()) {
//        renderObjects.insert(rObjs.front());
//        rObjs.pop();
//    }
//    return true;
//}

void RendererCore::ExecuteDrawCall(const DrawCall * drawCall) {

//geometry render test (as stupid as SDL copy rendering)
    //auto pos = rObj->GetWorldPosition();
    //auto rect = rObj->GetRect();
    //
    //SDL_Vertex v[4];
    //v[0] = { {(float)pos.x - rect->w, (float)pos.y - rect->h}, {255,255,255,255}, {0,0} };
    //v[1] = { {(float)pos.x + rect->w, (float)pos.y - rect->h}, {255,255,255,255}, {1,0} };
    //v[2] = { {(float)pos.x - rect->w, (float)pos.y + rect->h}, {255,255,255,255}, {0,1} };
    //v[3] = { {(float)pos.x + rect->w, (float)pos.y + rect->h}, {255,255,255,255}, {1,1} };

    //int i[6];
    //i[0] = 0;
    //i[1] = 1;
    //i[2] = 2;
    //i[3] = 1;
    //i[4] = 2;
    //i[5] = 3;

    //SDL_RenderGeometry(renderer, rObj->GetTexture().get(), v, 4, i, 6 );
//geometry render test 

    SDL_RenderCopyEx(
        renderer,
        drawCall->renderElement->GetTexture().get(),
        NULL,
        &drawCall->rect,
        drawCall->rotation,
        &drawCall->rotationPivot,
        SDL_FLIP_NONE
    );
}
void RendererCore::DrawSorted(DrawQueue_t& drawCalls) {
    while (drawCalls.size()) {
        ExecuteDrawCall(&drawCalls.top());
        drawCalls.pop();
    }
}
bool RendererCore::Update(DrawQueue_t& rObjs) {
    ClearScreen();
    DrawSorted(rObjs);

    UpdateScreen();
    return true;
}
