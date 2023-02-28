#pragma once
#include "RendererUtils.h"
#include "CoreTypes.h"

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
	void DrawRenderObject(RenderObject* rObj);
	void DrawSorted(DrawQueue_t& rObjs);

public:
	RendererCore();
	~RendererCore();
	bool Init(int w, int h);
	
	SDL_Window* GetWindow() { return window; }
	SDL_Renderer* GetRenderer() { return renderer; }
	SDL_Surface* GetScreenSurface() { return screen; }

	bool Update(DrawQueue_t& rObjs);
};

