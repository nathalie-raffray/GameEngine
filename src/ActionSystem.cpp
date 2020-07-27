#include "ActionSystem.h"
#include "AssetStorage.h"

#include <fstream>

void ActionSystem::init(const std::string& filePath)
{
	//load input config. initialize actionmap.
	json js;
	std::ifstream i(filePath);
	i >> js;

	for (auto& jj : js.items())
	{
		actionMap[GetActionNameValue(jj.key().c_str())] = jj.value();
	}
}


bool ActionSystem::getActionValue(ActionName actionName)
{
	Input& input = actionMap[actionName];
	
	switch (InputComponent::d)
	{

	case InputComponent::PC:
		switch (input.pctag)
		{
		case Input::keyboard:
			return sf::Keyboard::isKeyPressed(input.keyboardmouseinput.key);
			
			//return sf::Keyboard::(input.keyboardmouseinput.key);

		case Input::mousebutton:
			return sf::Mouse::isButtonPressed(input.keyboardmouseinput.mouseButton);
		}
		break;

	case InputComponent::XBOXCONTROLLER:
		switch (input.xboxtag)
		{
		case Input::joystickaxis:
			{
				float axispos = sf::Joystick::getAxisPosition(InputComponent::joystickID, input.joystickinput.joystickaxis.axis);
				return (axispos * static_cast<int>(input.joystickinput.joystickaxis.dir) > 0);
			}
		case Input::joystickbutton:
			return sf::Joystick::isButtonPressed(InputComponent::joystickID, input.joystickinput.button);
		}
		break;
	}
	return false;
}

/*
void from_json(const json& j, ActionSystem& ac)
{
	for (auto& jj : j.items())
	{
		ac.actionMap[GetActionNameValue(jj.key().c_str())] = jj.value();
	}
}

void to_json(json& j, const ActionSystem& ac)
{
	for (auto& el : ac.actionMap)
	{
		j[GetString(el.first)] = el.second;
	}
}
*/