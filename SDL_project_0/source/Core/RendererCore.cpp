#include "stdafx.h"
#include "RendererCore.h"
#include "Camera.h"
#include "RenderableComponent.h"

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

Vector2i RendererCore::GetRenderWindowSize()
{
    Vector2i windowSize;
    SDL_GetWindowSize(window, &windowSize.x, &windowSize.y);
    return windowSize;
}

void RendererCore::ExecuteDrawCall(const DrawCall* drawCall, Camera* camera) {

    auto pos = drawCall->wTransform.position;
    //transform to camera space
    pos -= camera->GetAbsoluteTransform().position;
    //offset position so object's center appears in where pivot is located, not on the left-top corner
    pos -=  drawCall->size*drawCall->wTransform.pivot;
    //scale on-screen offset of object caused by camera zoom
    pos *= camera->zoom;
    
    SDL_Rect finalDstRect= {(int)pos.x, (int)pos.y,int(drawCall->size.x* camera->zoom),int(drawCall->size.y* camera->zoom)};

    //offset to center of the screen
    finalDstRect.x += GetRenderWindowSize().x/2;
    finalDstRect.y += GetRenderWindowSize().y/2;

    SDL_RenderCopyEx(
        renderer,
        drawCall->texture,
        &drawCall->srcRect,
        &finalDstRect,
        drawCall->rotation,
        &drawCall->rotationPivot,
        SDL_FLIP_NONE
    );
}

DrawQueue_t RendererCore::GetDrawCallsAfterCulling(DrawQueue_t drawCalls, Camera* camera)
{
    auto cullRect = camera->GetRenderRect();
    DrawQueue_t leftDrawCalls;
    for(; !drawCalls.empty(); drawCalls.pop())
    {
        //drawCall borders
        auto left = drawCalls.top().wTransform.position.x - drawCalls.top().size.x * (double)drawCalls.top().wTransform.pivot.x;
        auto top = drawCalls.top().wTransform.position.y - drawCalls.top().size.y * (double)drawCalls.top().wTransform.pivot.y;
        auto right = drawCalls.top().wTransform.position.x + (drawCalls.top().size.x - drawCalls.top().size.x * (double)drawCalls.top().wTransform.pivot.x);
        auto bot = drawCalls.top().wTransform.position.y + (drawCalls.top().size.y - drawCalls.top().size.y * (double)drawCalls.top().wTransform.pivot.y);

        if(
            left > cullRect.position.x+cullRect.extents.x   ||
            right < cullRect.position.x-cullRect.extents.x  ||
            top > cullRect.position.y+cullRect.extents.y    ||
            bot < cullRect.position.y-cullRect.extents.y  
            ) continue;

        // if (left > cullRect.position.x+cullRect.extents.x)
        // {
        //     continue;
        // }
        // if (right < cullRect.position.x-cullRect.extents.x)
        // {
        //     continue;
        // }
        // if (bot < cullRect.position.y-cullRect.extents.y)
        // {
        //     continue;
        // }
        // if (top > cullRect.position.y+cullRect.extents.y)
        // {
        //     continue;
        // }
        leftDrawCalls.push(drawCalls.top());
    }
    return leftDrawCalls;
}

void RendererCore::DrawCulled(DrawQueue_t& drawCalls, Camera* camera) {

    DrawQueue_t leftDrawCalls = GetDrawCallsAfterCulling(drawCalls, camera);
    printf("%d\n", (int)leftDrawCalls.size());
    for(; !leftDrawCalls.empty(); leftDrawCalls.pop())
    {
        ExecuteDrawCall(&leftDrawCalls.top(), camera);
    }
}

void RendererCore::RegisterCamera(Camera* cam)
{
    if (cameras.find(cam) != cameras.end())  return;
    cameras.insert(cam);
}

void RendererCore::UnregisterCamera(Camera* cam)
{
    if (cameras.find(cam) == cameras.end())  return;
    cameras.erase(cam);
}

bool RendererCore::Update(DrawQueue_t& drawCalls) {
    ClearScreen();

    for(auto camera : cameras)
    {
        DrawCulled(drawCalls, camera);
    }
    //debug pixel 
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0x00);
    SDL_RenderDrawPoint(renderer, GetRenderWindowSize().x/2, GetRenderWindowSize().y/2);
    //debug pixel 
    UpdateScreen();
    return true;
}
