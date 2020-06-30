#pragma once
#include "json.hpp"

using nlohmann::json;

#include <optional>
#include <iostream>

//--------------------------------------------------------------------------------------------------

template<typename T>
inline std::optional<T> has_field(const json& obj, const std::string& key) {
	try {
		return obj.at(key).get<T>();
	}
	catch (const json::exception&) {
		return std::nullopt;
	}
}

//--------------------------------------------------------------------------------------------------

template<>
inline std::optional<json> has_field<json>(const json& obj, const std::string& key) {
	try {
		return obj.at(key);
	}
	catch (const json::exception&) {
		return std::nullopt;
	}
}

//--------------------------------------------------------------------------------------------------

#define TRY_PARSE(statement) try\
{\
	statement;\
}\
catch (json::parse_error & e)\
{\
	std::cout << "message: " << e.what() << '\n' << "exception id: " << e.id << '\n'\
		<< "byte position of error: " << e.byte << std::endl;\
}\
catch (json::exception&) {\
}

//--------------------------------------------------------------------------------------------------

#define TRY_PARSE_ELSE(statement1, statement2) try\
{\
	statement1;\
}\
catch (json::parse_error & e)\
{\
	std::cout << "message: " << e.what() << '\n' << "exception id: " << e.id << '\n'\
		<< "byte position of error: " << e.byte << std::endl;\
	statement2;\
}catch (json::exception&)\
{\
	statement2;\
}

//--------------------------------------------------------------------------------------------------

#include "jsonSFML.h"