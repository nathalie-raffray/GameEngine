#pragma once

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>

#include <unordered_map>
#include <string>

#include "System.h"

enum class InputSystem
{
	KEYBOARD, XBOXCONTROLLER
};

/*
enum class ActionName
{
	Left, Right, Up, Down, Start, Select, ButtonB, ButtonA, TurboB, TurboA
};
*/

using ActionName = std::string;

struct ActionComponent
{
	//ActionName name; //jump, walk left, blah...
	//Input input;
	std::string name;

	/*KEYBOARD OR MOUSE*/
	bool keyboardmouse;

	char key;
	bool leftrightmousebutton;
	/*JOYSTICK AXIS OR JOYSTICK BUTTON*/
	bool axisbutton;

	char axis;
	bool direction;
	char button;
};
 
struct Input
{
	enum tag {
		keyboard, mousebutton, joystickaxis, joystickbutton
	};

	tag keyboardmouse;
	union KeyboardMouseInput
	{
		sf::Keyboard::Key key;
		sf::Mouse::Button mouseButton;
	};

	tag joystick;
	union JoystickInput
	{
		struct JoystickAxis
		{
			enum Direction { POSITIVE = true, NEGATIVE = false };

			sf::Joystick::Axis axis;
			Direction dir;
		} joystickaxis;

		unsigned int button;
	};
};

class ActionSystem //system???
{
public:
	bool getActionValue(const ActionName& actionName);

	//float getActionValueFloat(const ActionName& actionName);
private:
	std::unordered_map<ActionName, Input> actionMap;
};

struct Camera : public System
{
	bool isValid(EntityHandle eh)
	{
		return (eh->has<SpriteComponent>() || eh->has<AnimationComponent>());
	}
	
	void update(float) override 
	{
		for (auto e : m_entities)
		{
			//
			//auto position = e->get<AnimationComponent>()->
			sf::Sprite s;
		}
	}
	
	EntityHandle center;

	float x;
	float y; //bottom lefthand coords
	//subtract from these when you save the level while editing w/level editor
};

//transform 

//sf::Transform

/*
struct RenderComponent
{
	unsigned int layer;

	#ifDEBUG
	static const char* componentName = "RenderComponent";
	#endif
}

when you add entities to rendering system you make sure to add them in order of rendercomponent
so that when you update, you draw in that order 


*/

/*
tilemap.json
{"spriteids" = ["tree", "dirt", "sky"],
"tilemap" = [[2, 2, 2],
			[2, 0, 2],
			[1, 1, 1]]
}
*/
/*struct Component;
std::unordered_map<std::string, Component> componentMap;
#define AddComponent(x) 
or, just avoid the fucking trouble, make em manually 
*/
/*
EntityTemplate editor
add Components, with their data, with an EntityTemplateComponent with a name
-----> load that into assets

save in an entityasset.json

make it an entity.

then in entity class, make a clone function. 
*/

/*
level editor IMGUI
for all entitytemplates with nameComponents, you can select one
and then you can edit all component data as well as drag it around
*/

/*bool Jump() { return isSpaceDown() || isAPressed(); } DATA DRIVEN ? ? ?

ActionSystem

actionstate<ActionName, ActionValue>
actionmap<ActionName, Input>
update actionstate every frame

ActionValue getActionValue(ActionNAme) {}

class BRAIN()
{
	virtual getActionValue(Action) {}
}

class GOOMBABRAIN()
{

}

class AISystem : public GOOMBRABRAIN
{

}

void jump()
{
	if (AIsYTEM::getActionValue(Jump))
	{
		transform.position.y += 1;
	}
}*/