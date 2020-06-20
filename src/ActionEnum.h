#pragma once

#include "EnumFactory.h"
#define ACTION_ENUM(XX) \
    XX(Left,) \
    XX(Right,) \
    XX(Up,) \
    XX(Down,) \
    XX(Start,) \
    XX(Select,) \
    XX(ButtonA,) \
    XX(ButtonB,) \
    XX(TurboA,) \
    XX(TurboB,) \


DECLARE_ENUM(ActionName, ACTION_ENUM)