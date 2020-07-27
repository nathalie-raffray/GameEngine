#pragma once
#include "EnumFactory.h"
#define SIDE_ENUM(XX, enumtype) \
    XX(left,,enumtype) \
    XX(right,,enumtype) \
    XX(top,,enumtype) \
    XX(bottom,,enumtype) \
    XX(all,,enumtype) \
	XX(none,,enumtype) \


DECLARE_ENUM(side, SIDE_ENUM)
