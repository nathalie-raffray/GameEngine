#pragma once
#include <vector>
#include <memory>
#include <bitset>
#include <unordered_map>


class Entity;


class EntityRegistry
{
public:
	std::vector<Entity> entities;
};

class Component
{
	virtual ~Component();

};

//using ComponentId = std::size_t;
/*
struct ComponentRegistryBase;
template<typename ComponentType>
struct ComponentRegistry;

struct ComponentRegistryManager
{
	std::vector<std::unique_ptr<ComponentRegistryBase>> component_registry; //need to know what index each component registry base is at 

	template<typename ComponentType>
	inline const std::size_t& getIndex() {
		static std::size_t index = component_registry.size() - 1;
		return index;
	};

	template<typename ComponentType>
	const std::vector<ComponentType>& operator->()
	{
		auto& index = getIndex<ComponentType>();
		if (index == component_registry.size() - 1)
			component_registry.emplace_back(std::make_unique<ComponentRegistry<ComponentType>>);
		return static_cast<ComponentRegistry<ComponentType>*>(component_registry[index])->components; //dynamic_cast :(( ?
	};

};

struct ComponentRegistryBase
{
	virtual ~ComponentRegistryBase() {}
};
*/
template<typename ComponentType>
struct ComponentRegistry 
{
	static std::vector<ComponentType> components;

};

template<typename ComponentType>
std::vector<ComponentType> ComponentRegistry<ComponentType>::components = {};


template<typename T>
struct ComponentHandle //PLAIN OLD DATA STRUCTURE
{
	std::size_t m_Handle;
	
	T* operator->()
	{
		return &ComponentRegistry<T>::components[componentIds[m_Handle]];
	}
	T& operator*()
	{
		return ComponentRegistry<T>::components[componentIds[m_Handle]];
	}
};

using ComponentId = std::size_t;

//dynamic inheritance to add member variable componentIds? howwww
class ComponentPunchCard 
{
public:

	template<typename T, typename... TArgs>
	void add(TArgs&& ...mArgs)
	{
		if(hasComponent<T>()) return;
		ComponentRegistry<T>::components.emplace_back(std::forward<TArgs>(mArgs)...);
		componentIds.emplace_back(ComponentRegistry<T>::components.size() - 1);
		setComponentId<T>();
		component_bitset<T>(true, true);
	}

	template<typename T>
	inline ComponentHandle<T> get()
	{
		//if (!hasComponent<T>()) return nullptr; //make this an assert
		return { getComponentId<T>() };
	}

	template<typename T>
	inline ComponentId& getId()
	{
		if (!hasComponent<T>()) return -1; //make this an assert
		return getComponentId<T>();
	}

	template<typename T>
	void remove()
	{
		if (!hasComponent<T>()) return;
		component_bitset<T>(false, false);
		ComponentRegistry<T>::components.erase(componentIds[getComponentId<T>()]);
	}
	
	template<typename T>
	inline bool has()
	{
		return component_bitset<T>(true);
	}

private:
	std::vector<std::size_t> componentIds;

	inline ComponentId getNewComponentId()
	{
		static ComponentId id = 0;
		return id++;
	}

	template<typename ComponentType>
	inline ComponentId& getComponentId() //make this private otherwise you dont want to be returning a reference 
	{
		static ComponentId id = getNewComponentId();
		return id;
	}

	template<typename ComponentType>
	inline ComponentId& setComponentId() //make this private otherwise you dont want to be returning a reference 
	{
		return getComponentId<ComponentType>();
	}

	template<typename ComponentType>
	inline bool component_bitset(bool getset, bool newbit = false) //make this private otherwise you dont want to be returning a reference 
	{
		static bool bit = newbit;
		return bit = getset ? bit : newbit;  //if get is true, return bit
											//if set is true, make bit = newbit and return bit
	}
};


class Entity : public ComponentPunchCard
{
private:
	bool m_isActive;
};

class EntityHandle
{
public:
	Entity* operator->()
	{
		//return &Game::registry->entities[m_index];
	}
private:
	unsigned int m_index;
};

class SomeSystem
{
	std::vector<EntityHandle> m_entities;
};
