#pragma once
#include <vector>
#include <memory>
#include <any>
#include <unordered_map>
//componentRegistrymanager
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
constexpr inline ComponentId& getComponentId()  //put this outside of here, so that anyone can call this, same componentId for each component everywhere
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
	//static std::vector<std::any>& components;
	//static std::unique_ptr<std::vector<std::any>> components;
	static std::vector<std::any>* components;

};
*/

/*
struct Component {};

struct component_registry_byhandle
{
	/*static std::vector< std::vector<std::any>& > all_components;

	static auto& at(int index)
	{
		ASSERT(index < all_components.size());
		return all_components[index];
	}

	void add(std::vector<std::any>& components)
	{
		all_components.emplace_back(components);
	}
	void add()
	{

	}

	static std::vector<std::any>& components;

	//static std::unordered_map<std::size_t, component_registry_base*> map;
};*/

struct component_registry_manager
{
	template<typename ComponentType>
	static void init()
	{
		static bool init = false;
		if (init) return;
		
		//std::size_t& h = component_registry<ComponentType>::handle; 
		//component_registry_byhandle::add(component_registry<ComponentType>::components);
		//component_registry_byhandle<0>::test = false;
		
		//component_registry_byhandle<0>::components = component_registry<ComponentType>::components; //initializes components
		//component_registry_byhandle<0>::components = std::make_unique<std::vector<std::any>>(component_registry<ComponentType>::components); //initializes components
		//component_registry_byhandle<0>::components = &component_registry<ComponentType>::components; //initializes components

		map[getComponentId<ComponentType>()] = component_registry<ComponentType>();

		//component_registry_byhandle<component_registry<ComponentType>::handle>::components = component_registry<ComponentType>::components; //initializes components
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

//template<typename ComponentType>
//bool init = false;

/*
Since it is part of a template, as with all templates the compiler will make sure
it's only defined once.
*/

struct ComponentRegistryManager
{
	//std::vector<std::unique_ptr<ComponentRegistry<std::any>>> component_registry_manager;
	//std::unordered_map<std::size_t, ComponentRegistry<std::any>&> component_registry_map;

	/*template<typename ComponentType>
	std::size_t get()
	{
		bool i = ComponentRegistry<T>::init;
		std::size_t h = ComponentRegistry<T>::handle;
		if (!i)
		{
			component_registry_manager.emplace_back(std::make_unique(ComponentRegistry<T>::components));
		}
		/*std::size_t h = ComponentRegistry<T>::handle;
		if (h == component_registry_manager.size())
		{
			component_registry_manager.emplace_back(std::make_unique(ComponentRegistry<T>::components));
		}
		return h;
	}
	template<typename ComponentType>
	std::vector<ComponentType>* get(std::size_t handle)
	{
		return component_registry_manager[handle].get();
	}
	*/


	//must be called before get or any other functions
	/*template<typename ComponentType>
	static std::size_t getHandle()
	{
		static std::size_t h = ComponentRegistry<ComponentType>::handle; //creates ComponentRegistry<T> first time it runs
		if (init<h>()) return h;

		get<h, ComponentType>(); //to be more optimal this should only run once, the first time get() is called
		return h;
	};

	template<std::size_t handle>
	static bool init()
	{
		static bool init = false;
		bool temp = init;
		init = true;
		return init;
	};
	
	template<std::size_t handle, typename ComponentType = void>
	static auto get()
	{
		ASSERT(init<handle>());
		static std::vector<ComponentType>& components = ComponentRegistry<ComponentType>::components; //this can become invalid tho...
		return components;
	};

	template<typename ComponentType, typename... TArgs>
	static std::size_t add(TArgs&& ...mArgs)
	{
		ASSERT(init<handle>());
		ComponentRegistry<ComponentType>::components.emplace_back(std::forward<TArgs>(mArgs)...);
	};*/



	
};


/*struct ComponentRegistryManager
{
	//template<typename ComponentType>
	//static std::vector<ComponentType> components;
	void operator[](int handle)
	{
		//handle -> type
	}
	//template<typename ComponentType>
	//static std::vector<ComponentRegistry<ComponentType>> components;
};*/

template<typename T>
struct ComponentHandle //PLAIN OLD DATA STRUCTURE
{
	std::size_t m_Handle;

	T* operator->()
	{
		//return &component_registry<T>::components[m_Handle];
		return &std::any_cast<T>(component_registry_manager::get<T>()[m_Handle]); //definitelyneed to make that more readable

	}
	T& operator*()
	{
		//return component_registry<T>::components[m_Handle];
		return std::any_cast<T>(component_registry_manager::get<T>()[m_Handle]);

	}
};