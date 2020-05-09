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
		//SAD(0); SAD(1); SAD(2); SAD(3);
		compile_time_iterate();

		//this wont work :(
		/*for (std::size_t cr_handle = 0; cr_handle < maxComponents; ++cr_handle)
		{
			auto& components = component_registry_byhandle<cr_handle>::components;
			components.erase(components.begin() + componentIds[cr_handle]);
		}*/

		/*
		for (std::size_t cr_handle = 0; cr_handle < maxComponents; ++cr_handle)
		{
			if (componentIds[cr_handle] == INVALID) continue;
			auto& components = component_registry_byhandle::at(cr_handle);
			components.erase(components.begin() + componentIds[cr_handle]);
		}
		*/

	}


	template<typename T, typename... TArgs>
	void add(TArgs&& ...mArgs)
	{
		ASSERT(!has<T>());
		//I think it will just be here that I add to the component registry
		//auto cr_handle = ComponentRegistryManager::set<T>();

		component_registry_manager::init<T>();
	
		auto cr_handle = getComponentId<T>();
		//component_registry<T>::components.emplace_back(std::forward<TArgs>(mArgs)...);
		component_registry_manager::get<T>().emplace_back(std::forward<TArgs>(mArgs)...);
			//components.emplace_back(std::forward<TArgs>(mArgs)...);

		//auto c_handle = component_registry_manager<T>::components.size() - 1;
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
		//component_registry<T>::components.erase(componentIds[getComponentId<T>()]);
		component_registry_manager::get<T>().erase(componentIds[getComponentId<T>()]);
		componentIds[getComponentId<T>()] = INVALID;
	}

	template<typename T>
	inline bool has()
	{
		//return component_bitset<T>(true, false);
		return !(componentIds[getComponentId<T>()] == INVALID);
	}

private:

	//std::vector<std::unique_ptr> componentRegistries;
	std::vector<std::size_t> componentIds; //make it equal size of maxComponents, each slot corresponds to a component, when there is no component = -1
	
	std::unordered_map<std::size_t, std::size_t> ids;
	

	//ComponentId new_id = 0;
	//bitset
	/*
	inline ComponentId getNewComponentId()
	{
		//static ComponentId id = 0;
		//return id++;
		return new_id++;
	}

	template<typename ComponentType>
	inline ComponentId& getComponentId()  //put this outside of here, so that anyone can call this, same componentId for each component everywhere
	{
		static ComponentId id = getNewComponentId();
		return id;
	}*/

	/*template<typename ComponentType>
	inline ComponentId& setComponentId()
	{
		return getComponentId<ComponentType>();
	}*/

	/*template<typename ComponentType>
	inline bool component_bitset(bool getset, bool newbit) 
	{
		static bool bit = newbit;
		return bit = getset ? bit : newbit;  //if get is true, return bit
											//if set is true, make bit = newbit and return bit
	}*/
};