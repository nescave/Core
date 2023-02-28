#pragma once
#include "Vector2.h"
typedef std::vector<std::function<void()>> buttonAction;
class Input
{
private:
	SDL_Event e;
	inline static std::unordered_map<SDL_Keycode, int> actionButtons;
	inline static std::unordered_map<int, int> mouseActionButtons;
	inline static std::unordered_map<SDL_Keycode, buttonAction> actionsMap;
	//inline static std::unordered_map<int, buttonAction> mouseActionsMap;
	inline static Vector2i mousePosition;
	bool quitEvent = false;
public:
	~Input();
	bool Init();
	void ProcessInput();
	bool GetQuitEvent() { return quitEvent; }
	static void AddActionButton(int actionButtonEnum, SDL_Keycode key);
	static void AddActionMouseButton(int actionButtonEnum, int button);

	static void RegisterAction(int actionButtonEnum, std::function<void()> f);
	static Vector2i GetPointerPosition();
	//static void RegisterSmth
};

