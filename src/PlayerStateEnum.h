#pragma once
#include "EnumFactory.h"
#define PLAYERSTATE_ENUM(XX, enumtype) \
    XX(little,,enumtype) \
    XX(mushroom,,enumtype) \
    XX(raccoon,,enumtype) \
    XX(star,,enumtype) \
	XX(fire,,enumtype) \
	XX(fire_raccoon,,enumtype) \
    XX(dead,,enumtype) \


DECLARE_ENUM(player_state, PLAYERSTATE_ENUM)
