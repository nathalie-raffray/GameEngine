#pragma once
#include <vector>
#include <string>
#include <utility>
#include <type_traits>
#include "ComponentRegistry.h"

#if _DEBUG
#define ASSERT(x) if(!(x)) __debugbreak();
#else 
#define ASSERT(x) (x)
#endif

using ComponentId = std::size_t;

constexpr std::size_t maxComponents = 32;
constexpr std::size_t INVALID = std::string::npos;

class ComponentPunchCard
{
public:

	ComponentPunchCard() : componentIds(std::vector<std::size_t>(maxComponents, INVALID)) {}

	void compile_time_iterate(std::integral_constant<std::size_t, maxComponents>)
	{
		//end recursion
	}
	template<std::size_t cr_handle = 0>
	void compile_time_iterate(std::integral_constant<std::size_t, cr_handle> = std::integral_constant<std::size_t, 0>())
	{
		//in essence std::integral_constant<int, 0> and std::integral_constant<int, 1> are two completely different types
		if (componentIds[cr_handle] != INVALID)
		{
			//auto& components = component_registry_byhandle<cr_handle>::components;
			//components.erase(components.begin() + componentIds[cr_handle]);
			//components->erase(components->begin() + componentIds[cr_handle]);

		}

		compile_time_iterate(std::integral_constant<std::size_t, cr_handle + 1>());
		//when cr_handle+1 = maxComponents, the compiler will choose a function without a template before one that does have a template.
		//since the compiler can find a function signature that works without having to instantiate a template, it prefers to choose the former.
		//this process is known as overload resolution under th heading "best viable function"
	}
	~ComponentPunchCard()
	{
		//how to erase all the correct components
		compile_time_iterate();

		//this wont work :(
		/*
		for (std::size_t cr_handle = 0; cr_handle < maxComponents; ++cr_handle)
		{
			if (componentIds[cr_handle] == INVALID) continue;
			auto& components = component_registry_byhandle<cr_handle>::components;
			components.erase(components.begin() + componentIds[cr_handle]);
		}
		*/
	}


	template<typename T, typename... TArgs>
	void add(TArgs&& ...mArgs)
	{
		ASSERT(!has<T>());
		component_registry_manager::init<T>();
	
		auto cr_handle = getComponentId<T>();

		component_registry_manager::get<T>().emplace_back(std::forward<TArgs>(mArgs)...);

		auto c_handle = component_registry_manager::get<T>().size() - 1;

		componentIds[cr_handle] = c_handle;

	}

	template<typename T>
	inline ComponentHandle<T> get()
	{
		ASSERT(has<T>());
		return { componentIds[getComponentId<T>()] };
	}

	template<typename T>
	inline ComponentId& getId()
	{
		ASSERT(has<T>());
		return getComponentId<T>();
	}

	template<typename T>
	void remove()
	{
		ASSERT(has<T>());
		component_registry_manager::get<T>().erase(componentIds[getComponentId<T>()]);
		componentIds[getComponentId<T>()] = INVALID;
	}

	template<typename T>
	inline bool has()
	{
		return !(componentIds[getComponentId<T>()] == INVALID);
	}

private:

	std::vector<std::size_t> componentIds; //make it equal size of maxComponents, each slot corresponds to a component, when there is no component = INVALID
	
};