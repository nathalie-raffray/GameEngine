#include "Input.h"

void from_json(const json& j, Input& ac)
{
	json jPC = j["PC"];
	if (jPC["input"] == "LMB")
	{
		ac.pctag = Input::mousebutton;
		ac.keyboardmouseinput.mouseButton = sf::Mouse::Button::Left;
	}
	else if (jPC["input"] == "RMB")
	{
		ac.pctag = Input::mousebutton;
		ac.keyboardmouseinput.mouseButton = sf::Mouse::Button::Right;
	}
	else {
		ac.pctag = Input::keyboard;
		ac.keyboardmouseinput.key = sf::Keyboard::Key(jPC["input"]);
	}

	json jXbox = j["XBOX"];
	if (jXbox["input"] == "joystick")
	{
		ac.xboxtag = Input::joystickaxis;
		switch (jXbox["axis"].get<std::string>()[0])
		{
		case 'x':
			ac.joystickinput.joystickaxis.axis = sf::Joystick::Axis::X;
			break;
		case 'y':
			ac.joystickinput.joystickaxis.axis = sf::Joystick::Axis::Y;
			break;
		}
		ac.joystickinput.joystickaxis.dir = (Input::JoystickInput::JoystickAxis::Direction)jXbox["direction"].get<int>();
	}
	else if (jXbox["input"] == "button")
	{
		ac.xboxtag = Input::joystickbutton;
		//ac.joystickinput.button = sf::Joystick::getIdentification(inputSystem.joystick)
	}
}

void to_json(json& j, const Input& ac)
{
	switch (ac.pctag)
	{
	case  Input::mousebutton:
		switch (ac.keyboardmouseinput.mouseButton)
		{
		case sf::Mouse::Button::Left:
			j["PC"]["input"] = "LMB";
			break;
		case sf::Mouse::Button::Right:
			j["PC"]["input"] = "RMB";
			break;
		}
		break;
	case  Input::keyboard:
		j["PC"]["input"] = static_cast<int>(ac.keyboardmouseinput.key);
		break;
	}

	switch (ac.xboxtag)
	{
	case  Input::joystickaxis:
		j["XBOX"]["input"] = "joystick";

		switch (ac.joystickinput.joystickaxis.axis)
		{
		case sf::Joystick::Axis::X:
			j["XBOX"]["axis"] = "x";
			break;
		case sf::Joystick::Axis::Y:
			j["PC"]["axis"] = "y";
			break;
		}
		j["PC"]["direction"] = static_cast<int>(ac.joystickinput.joystickaxis.dir);
		break;
	case  Input::joystickbutton:
		j["XBOX"]["input"] = "button";

		//j["XBOX"]["input"]["button"] = static_cast<int>(ac.joystickinput.button);
		break;
	}
}
