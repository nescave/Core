#include "stdafx.h"
#include "RendererCore.h"
#include "Camera.h"
#include "RenderableComponent.h"

bool RendererCore::CameraRegistered(Camera* cam)
{
    return cameras.find(cam) != cameras.end();
}

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

DrawQueue_t RendererCore::GetCulledAndSortedDrawCalls(const std::vector<DrawCall>& drawCalls, Camera* camera)
{
    auto cullRect = camera->GetRenderRect();
    DrawQueue_t leftDrawCalls;
    for(const auto& drawCall : drawCalls)
    {
        //drawCall borders
        auto left = drawCall.wTransform.position.x - drawCall.size.x * (double)drawCall.wTransform.pivot.x;
        auto top = drawCall.wTransform.position.y - drawCall.size.y * (double)drawCall.wTransform.pivot.y;
        auto right = drawCall.wTransform.position.x + (drawCall.size.x - drawCall.size.x * (double)drawCall.wTransform.pivot.x);
        auto bot = drawCall.wTransform.position.y + (drawCall.size.y - drawCall.size.y * (double)drawCall.wTransform.pivot.y);

        if(
            left > cullRect.position.x+cullRect.extents.x   ||
            right < cullRect.position.x-cullRect.extents.x  ||
            top > cullRect.position.y+cullRect.extents.y    ||
            bot < cullRect.position.y-cullRect.extents.y  
            ) continue;
        leftDrawCalls.push(drawCall);
    }
    return leftDrawCalls;
}

void RendererCore::Draw(std::vector<DrawCall>& drawCalls, Camera* camera) {

    DrawQueue_t leftDrawCalls = GetCulledAndSortedDrawCalls(drawCalls, camera);
    for(; !leftDrawCalls.empty(); leftDrawCalls.pop())
    {
        ExecuteDrawCall(&leftDrawCalls.top(), camera);
    }
}

void RendererCore::RegisterCamera(Camera* cam)
{
    if (CameraRegistered(cam))  return;
    if(cam->mainCamera)
    {
        for(auto& camera : cameras)
        {
            camera->mainCamera = false;
        }
    }
    cameras.insert(cam);
}

void RendererCore::UnregisterCamera(Camera* cam)
{
    if (!CameraRegistered(cam))  return;
    cameras.erase(cam);
}

void RendererCore::SetMain(Camera* cam)
{
    if (!CameraRegistered(cam)) return;
    for(auto& camera : cameras)
    {
        camera->mainCamera = false;
    }
    cam->mainCamera = true;
}

bool RendererCore::Update(std::vector<DrawCall>& drawCalls) {
    ClearScreen();

    for(auto camera : cameras)
    {
        if(camera->mainCamera) Draw(drawCalls, camera); //draws to main screen
    }
    UpdateScreen();
    return true;
}
