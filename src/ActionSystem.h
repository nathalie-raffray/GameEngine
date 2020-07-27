#pragma once
#include <unordered_map>
#include <string>

#include "ActionEnum.h"
#include "Input.h"

#include <SFML/Window/Event.hpp>

#include "json_serialization.h"

struct InputConfig
{
	enum Device {
		PC, XBOXCONTROLLER
	};
	static inline Device device;
	static inline unsigned int joystickID;
};


class ActionSystem 
{
public:
	static void init(const std::string& filePath);

	static bool getActionValue(ActionName actionName);

	static inline std::unordered_map<ActionName, Input> actionMap;
};

