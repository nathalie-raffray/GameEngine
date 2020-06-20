#pragma once
#include <unordered_map>
#include <string>

#include "ActionEnum.h"
#include "Input.h"

#include "json.hpp"

using nlohmann::json;

struct InputComponent
{
	enum Device {
		PC, XBOXCONTROLLER
	};
	static inline Device d;
	static inline unsigned int joystickID;
};


class ActionSystem //system???
{
public:
	//ActionSystem(const std::string& filePath);

	static void init(const std::string& filePath);

	static bool getActionValue(ActionName actionName);

	//float getActionValueFloat(const ActionName& actionName);
	static inline std::unordered_map<ActionName, Input> actionMap;
};

void from_json(const json& j, ActionSystem& ac);
void to_json(json& j, const ActionSystem& ac);

//using ActionName = std::string;
/*
struct ActionComponent
{
	//ActionName name; //jump, walk left, blah...
	//Input input;
	//std::string name;
	//uint32_t id;
	ActionName action_name;

	//KEYBOARD OR MOUSE
	bool keyboardmouse;

	char key;
	bool leftrightmousebutton;
	//JOYSTICK AXIS OR JOYSTICK BUTTON
	bool axisbutton;

	char axis;
	bool direction;
	char button;
};
 */







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