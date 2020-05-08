#pragma once
#include <vector>
#include "ComponentRegistry.h"

#if _DEBUG
#define ASSERT(x) if(!(x)) __debugbreak();
#else 
#define ASSERT(x) (x)
#endif

using ComponentId = std::size_t;

//dynamic inheritance to add member variable componentIds? howwww
//template<typename T, T, ....>
class ComponentPunchCard
{
public:
	~ComponentPunchCard()
	{
		//how to erase all the correct components
	}

	template<typename T, typename... TArgs>
	void add(TArgs&& ...mArgs)
	{
		ASSERT(!has<T>());
		ComponentRegistry<T>::components.emplace_back(std::forward<TArgs>(mArgs)...);
		componentIds.emplace_back(ComponentRegistry<T>::components.size() - 1);
		setComponentId<T>();
		component_bitset<T>(false, true);
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
		component_bitset<T>(false, false);
		ComponentRegistry<T>::components.erase(componentIds[getComponentId<T>()]);
	}

	template<typename T>
	inline bool has()
	{
		return component_bitset<T>(true, false);
	}

private:

	//std::vector<std::unique_ptr> componentRegistries;
	std::vector<std::size_t> componentIds; //make it equal size of maxComponents, each slot corresponds to a component

	ComponentId new_id = 0;
	//bitset

	inline ComponentId getNewComponentId()
	{
		//static ComponentId id = 0;
		//return id++;
		return new_id++;
	}

	template<typename ComponentType>
	inline ComponentId& getComponentId()  
	{
		static ComponentId id = getNewComponentId();
		return id;
	}

	template<typename ComponentType>
	inline ComponentId& setComponentId()
	{
		return getComponentId<ComponentType>();
	}

	template<typename ComponentType>
	inline bool component_bitset(bool getset, bool newbit) 
	{
		static bool bit = newbit;
		return bit = getset ? bit : newbit;  //if get is true, return bit
											//if set is true, make bit = newbit and return bit
	}
};