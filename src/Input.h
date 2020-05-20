#pragma once
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>

class Input : public sf::Keyboard, public sf::Mouse, public sf::Joystick
{
	
};
