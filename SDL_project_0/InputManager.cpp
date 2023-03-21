#include "stdafx.h"
#include "InputManager.h"
#include "CoreActionButtons.h"

InputManager::~InputManager()
{
	//for (auto v : actionsMap) {
	//	delete &v;
	//}
}

bool InputManager::Init()
{
	//default input defined HERE for now
	AddActionButton(CONFIRM, SDLK_RETURN);
	AddActionButton(CANCEL, SDLK_ESCAPE);
	AddActionMouseButton(LMB, SDL_BUTTON_LEFT);
	RegisterAction(CANCEL, [this]() {this->quitEvent = true; });
	return true;
}
void InputManager::AddActionButton(int actionButtonEnum, SDL_Keycode key)
{
	if (actionButtons.find(key) != actionButtons.end()) {
		printf("%d button already exists!", actionButtonEnum);
		return;
	}
	actionButtons[key] = actionButtonEnum;
	actionsMap.emplace(actionButtonEnum, buttonAction() );
}

void InputManager::AddActionMouseButton(int actionButtonEnum, int button)
{
	if (mouseActionButtons.find(actionButtonEnum) != mouseActionButtons.end()) {
		printf("%d button already exists!", actionButtonEnum);
		return;
	}
	mouseActionButtons[button] = actionButtonEnum;
	actionsMap.emplace(actionButtonEnum, buttonAction());
}

void InputManager::RegisterAction(int actionButtonEnum, std::function<void()> f)
{
	actionsMap[actionButtonEnum].push_back(f);
}

Vector2i InputManager::GetPointerPosition()
{
	return mousePosition;
}

void InputManager::ProcessInput()
{
	while (SDL_PollEvent(&e)) {
		switch (e.type)
		{
		case SDL_KEYDOWN:
			if(!e.key.repeat){
			
				SDL_Keycode key = e.key.keysym.sym;
				if (actionsMap.find(actionButtons[key]) != actionsMap.end()) {
					for (auto f : actionsMap[actionButtons[key]]) {
						f();
					}
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.clicks > 0) {
				auto mb = e.button.button;
				if (actionsMap.find(mouseActionButtons[mb]) != actionsMap.end()) {
					for (auto f : actionsMap[mouseActionButtons[mb]]) {
						f();
					}
				}
			}
			break;
		case SDL_MOUSEMOTION:
			mousePosition.x = e.motion.x;
			mousePosition.y = e.motion.y;
			break;
		case SDL_QUIT:
			quitEvent = true;
			break;
		default:
			break;
		}
	}
}