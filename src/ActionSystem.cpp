#include "ActionSystem.h"
#include "AssetStorage.h"

#include <fstream>

//----------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------

bool ActionSystem::getActionValue(ActionName actionName)
{
	Input& input = actionMap[actionName];
	
	switch (InputConfig::device)
	{

	case InputConfig::PC:
		switch (input.pctag)
		{
		case Input::keyboard:
			return sf::Keyboard::isKeyPressed(input.keyboardmouseinput.key);
			
		case Input::mousebutton:
			return sf::Mouse::isButtonPressed(input.keyboardmouseinput.mouseButton);
		}
		break;

	case InputConfig::XBOXCONTROLLER:
		switch (input.xboxtag)
		{
		case Input::joystickaxis:
			{
				float axispos = sf::Joystick::getAxisPosition(InputConfig::joystickID, input.joystickinput.joystickaxis.axis);
				return (axispos * static_cast<int>(input.joystickinput.joystickaxis.dir) > 0);
			}
		case Input::joystickbutton:
			return sf::Joystick::isButtonPressed(InputConfig::joystickID, input.joystickinput.button);
		}
		break;
	}
	return false;
}

//----------------------------------------------------------------------------------------------
