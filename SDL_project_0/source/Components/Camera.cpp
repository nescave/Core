#include "stdafx.h"
#include "Camera.h"

#include "Core.h"
#include "RendererCore.h"

Camera::Camera() :
    zoom(1),
    clearAfterRender(true),
    mainCamera(false),
    renderTarget(nullptr)
{
    core->GetRendererCore().RegisterCamera(this);
}

Camera::~Camera()
{
    core->GetRendererCore().UnregisterCamera(this);
}
Rect<double> Camera::GetRenderRect()
{
    const auto position = GetPosition(); 
    Rect<double> cullRect;
    auto const windowSize = core->GetRendererCore().GetRenderWindowSize();
    cullRect.position = position;
    cullRect.extents = Vector2d(windowSize.x*.5/zoom, windowSize.y*.5/zoom);
    return cullRect;
}

void Camera::SetMain()
{
    core->GetRendererCore().SetMain(this);
}
