#pragma once
#include <vector>
#include <memory>
#include <any>
#include <unordered_map>

using ComponentId = std::size_t;

#if _DEBUG
#define ASSERT(x) if(!(x)) __debugbreak();
#else 
#define ASSERT(x) (x)
#endif


inline ComponentId getNewComponentId()
{
	static ComponentId id = 0;
	return id++;
}


template<typename ComponentType>
constexpr inline ComponentId& getComponentId()  
{
	static ComponentId id = getNewComponentId();
	return id;
}

template<typename ComponentType>
struct component_registry 
{
	//static std::vector<ComponentType> components;
	//static std::size_t handle;
	std::vector<ComponentType> components;

};
//definition of a non-template data member of a class template

/*template<typename ComponentType>
std::vector<ComponentType> component_registry<ComponentType>::components = {};

template<typename ComponentType>
std::size_t handle = getComponentId<ComponentType>();*/

/*
template<std::size_t handle> //where handle must be less than maxcomponents
struct component_registry_byhandle
{
	static std::vector<std::any>& components;
};
*/

struct component_registry_manager
{
	template<typename ComponentType>
	static void init()
	{
		static bool init = false;
		if (init) return;

		map[getComponentId<ComponentType>()] = component_registry<ComponentType>();

		init = true;
	}

	static std::vector<std::any>& get_byhandle(std::size_t handle)
	{
		ASSERT(map.count(handle) != 0);
		return map[handle].components;
	}

	template<typename ComponentType>
	static std::vector<std::any>& get()
	{
		auto handle = getComponentId<ComponentType>();
		ASSERT(map.count(handle) != 0);
		//return std::any_cast<ComponentType>(map[handle].components);
		return map[handle].components;
	}

	static std::unordered_map<std::size_t, component_registry<std::any>> map;
};
//component_registry<getComponentId<ComoponentType>>::components
//component_registry<handle>::components

template<typename T>
struct ComponentHandle 
{
	std::size_t m_Handle;

	T* operator->()
	{
		//return &component_registry<T>::components[m_Handle];
		return &std::any_cast<T>(component_registry_manager::get<T>()[m_Handle]); 

	}
	T& operator*()
	{
		//return component_registry<T>::components[m_Handle];
		return std::any_cast<T>(component_registry_manager::get<T>()[m_Handle]);

	}
};