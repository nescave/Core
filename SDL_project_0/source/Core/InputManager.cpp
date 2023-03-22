#include "stdafx.h"
#include "InputManager.h"
#include "CoreActionButtons.h"


static InputManager* imInst;

void InputManager::AddCoreButtons()
{
	AddActionButton(CONFIRM, SDLK_RETURN);
	AddActionButton(CANCEL, SDLK_ESCAPE);
	AddActionButton(UP, SDLK_UP);
	AddActionButton(LEFT, SDLK_LEFT);
	AddActionButton(DOWN, SDLK_DOWN);
	AddActionButton(RIGHT, SDLK_RIGHT);
	AddActionButton(W, SDLK_w);
	AddActionButton(A, SDLK_a);
	AddActionButton(S, SDLK_s);
	AddActionButton(D, SDLK_d);
	AddActionButton(L_SHIFT, SDLK_LSHIFT);
	AddActionButton(TAB, SDLK_TAB);

	AddActionMouseButton(LMB, SDL_BUTTON_LEFT);
	AddActionMouseButton(RMB, SDL_BUTTON_RIGHT);
	AddActionMouseButton(MMB, SDL_BUTTON_MIDDLE);

}

InputManager::InputManager() :
	e(SDL_Event())
{
	if(!imInst) imInst=this;
}

InputManager::~InputManager()
= default;

bool InputManager::Init(bool addCoreButtons)
{
	//default input defined HERE for now
	if(addCoreButtons) AddCoreButtons();
	RegisterAction(CANCEL, [this]() {this->quitEvent = true; });
	return true;
}

InputManager* InputManager::Get()
{
	return imInst; 
}

void InputManager::AddActionButton(int actionButtonEnum, SDL_Keycode key)
{
	if (actionButtons.find(key) != actionButtons.end()) {
		printf("%d button already exists!", actionButtonEnum);
		return;
	}
	actionButtons[key] = actionButtonEnum;
	actionsMap.emplace(actionButtonEnum, ButtonActions() );
}

void InputManager::AddActionMouseButton(int actionButtonEnum, int button)
{
	if (mouseActionButtons.find(actionButtonEnum) != mouseActionButtons.end()) {
		printf("%d button already exists!", actionButtonEnum);
		return;
	}
	mouseActionButtons[button] = actionButtonEnum;
	actionsMap.emplace(actionButtonEnum, ButtonActions());
}

void InputManager::RegisterAction(int actionButtonEnum, const std::function<void()>& f, EActionType type)
{
	actionsMap[actionButtonEnum].push_back(std::make_pair(f, type));
}

const Vector2d& InputManager::GetPointerScreenPosition() const
{
	return mousePosition;
}

void InputManager::ProcessInput()
{
	SDL_Keycode key;
	uint8_t mb;
	while (SDL_PollEvent(&e)) {
		switch (e.type)
		{
		case SDL_KEYDOWN:
			key = e.key.keysym.sym;
			if (actionsMap.find(actionButtons[key]) != actionsMap.end()) {
				for (auto& tpl : actionsMap[actionButtons[key]]) {
					if(!e.key.repeat &&
						(std::get<1>(tpl) == EActionType::REPETABLE ||
						std::get<1>(tpl) == EActionType::SINGLE))
					{
						std::get<0>(tpl)();
					}else if(!e.key.repeat && std::get<1>(tpl) == EActionType::CONTINUOUS)
					{
						continuousButtons.push_back(actionButtons[key]);
					}
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			mb = e.button.button;
			if (actionsMap.find(mouseActionButtons[mb]) != actionsMap.end()) {
				for (auto& tpl : actionsMap[mouseActionButtons[mb]]) {
					if(!(e.button.clicks >0) &&
						(std::get<1>(tpl) == EActionType::REPETABLE ||
						std::get<1>(tpl) == EActionType::SINGLE))
					{
						std::get<0>(tpl)();
					}else if(!(e.button.clicks >0) &&
						std::get<1>(tpl) == EActionType::CONTINUOUS)
					{
						continuousButtons.push_back(mouseActionButtons[mb]);
					}
				}
			}
			break;
		case SDL_KEYUP:
			key = e.key.keysym.sym;
			continuousButtons.remove(actionButtons[key]);
			break;
		case SDL_MOUSEBUTTONUP:
			mb = e.button.button;
			continuousButtons.remove(mouseActionButtons[mb]);
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
	for(auto button : continuousButtons)
	{
		for(auto& tpl : actionsMap[button])
		{
			std::get<0>(tpl)();
		}
	}
}