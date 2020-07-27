#pragma once
#include "EnumFactory.h"
#define ACTION_ENUM(XX, enumtype) \
    XX(Left,,enumtype) \
    XX(Right,,enumtype) \
    XX(Up,,enumtype) \
    XX(Down,,enumtype) \
    XX(Start,,enumtype) \
    XX(Select,,enumtype) \
    XX(ButtonA,,enumtype) \
    XX(ButtonB,,enumtype) \
    XX(TurboA,,enumtype) \
    XX(TurboB,,enumtype) \


DECLARE_ENUM(ActionName, ACTION_ENUM)