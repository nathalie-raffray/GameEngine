#pragma once
/*
EnumFactory.h
utility to refer to an enum by the string of the enum name, and vice versa.
Source: https://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c#202511
*/
#include <string.h>
// expansion macro for enum value definition
#define ENUM_VALUE(name,assign) name assign,

// expansion macro for enum to string conversion
#define ENUM_CASE(name,assign) case name: return #name;

// expansion macro for string to enum conversion
#define ENUM_STRCMP(name,assign) if (!strcmp(str,#name)) return name;

/// declare the access function and define enum values
#define DECLARE_ENUM(EnumType,ENUM_DEF) \
  enum EnumType { \
    Error, ENUM_DEF(ENUM_VALUE) \
  }; \
  const char *GetString(EnumType dummy); \
  EnumType Get##EnumType##Value(const char *string); \

/// define the access function names
#define DEFINE_ENUM(EnumType,ENUM_DEF) \
  const char *GetString(EnumType value) \
  { \
    switch(value) \
    { \
	  ENUM_DEF(ENUM_CASE) \
      default: return "Error"; /* handle input error */ \
    } \
  } \
  EnumType Get##EnumType##Value(const char* str) \
  { \
    ENUM_DEF(ENUM_STRCMP) \
    return (EnumType)Error; /* handle input error */ \
  } 