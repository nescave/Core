#pragma once
#include "Vector2.h"

enum class EActionType
{
	SINGLE,
	REPETABLE,	//fires once and after a while starts repeating with every update
	CONTINUOUS	//fires with every update when key is pressed
};
typedef std::vector<std::tuple<std::function<void()>, EActionType>> ButtonActions;

class InputManager
{
private:
	SDL_Event e;
	std::unordered_map<SDL_Keycode, int> actionButtons;
	std::unordered_map<int, int> mouseActionButtons;
	std::unordered_map<int, ButtonActions> actionsMap;
	std::list<int> continuousButtons;
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

	void RegisterAction(int actionButtonEnum, const std::function<void()>& f, EActionType type = EActionType::SINGLE);
	const Vector2d& GetPointerScreenPosition() const;
	//static void RegisterSmth
};
