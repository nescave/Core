#pragma once
#include "Vector2.h"
typedef std::vector<std::function<void()>> buttonAction;
class InputManager
{
private:
	SDL_Event e;
	std::unordered_map<SDL_Keycode, int> actionButtons;
	std::unordered_map<int, int> mouseActionButtons;
	std::unordered_map<SDL_Keycode, buttonAction> actionsMap;
	//inline static std::unordered_map<int, buttonAction> mouseActionsMap;
	Vector2d mousePosition;
	bool quitEvent = false;

	void AddCoreButtons();
public:
	InputManager();
	~InputManager();
	bool Init(bool addCoreButtons = true);
	static InputManager* Get();
	void ProcessInput();
	bool GetQuitEvent() { return quitEvent; }
	void AddActionButton(int actionButtonEnum, SDL_Keycode key);
	void AddActionMouseButton(int actionButtonEnum, int button);

	void RegisterAction(int actionButtonEnum, std::function<void()> f);
	const Vector2d& GetPointerScreenPosition() const;
	//static void RegisterSmth
};
