#pragma once
#include "RendererUtils.h"

class Camera;
class RendererCore
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screen;
	//std::priority_queue<RenderObject*, RenderObjectComparator> renderObjects;
	//std::priority_queue<RenderObject*, std::vector<RenderObject*>, RenderObjectComparator> renderObjects;
	void ClearScreen();
	void UpdateScreen();

	//bool AddRenderObjects(std::queue<RenderObject*> rObjs);
	void ExecuteDrawCall(const DrawCall* drawCall, Camera* camera);
	DrawQueue_t GetCulledAndSortedDrawCalls(const std::vector<DrawCall>& drawCalls, Camera* camera);
	void Draw(std::vector<DrawCall>& rObjs, Camera* camera);
	std::unordered_set<Camera*> cameras;
	bool CameraRegistered(Camera* cam);
	
public:
	RendererCore();
	~RendererCore();
	bool Init(int w, int h);
	
	SDL_Window* GetWindow() { return window; }
	SDL_Renderer* GetRenderer() { return renderer; }
	SDL_Surface* GetScreenSurface() { return screen; }

	void RegisterCamera(Camera* cam);
	void UnregisterCamera(Camera* cam);
	void SetMain(Camera* cam);
	bool Update(std::vector<DrawCall>& drawCalls);
	Vector2i GetRenderWindowSize();
};

