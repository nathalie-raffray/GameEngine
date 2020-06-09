#pragma once
#include <string>
#include "json.hpp"

using nlohmann::json;

#include "ComponentRegistry.h"

#if _DEBUG
#define ASSERT(x) if(!(x)) __debugbreak();
#else 
#define ASSERT(x) (x)
#endif

struct EntityHandle;

template<typename T>
struct component_handle
{
	uint32_t m_index = INVALID;

	T* operator->()
	{
		return &component_registry<T>::m_components[m_index];
	}
	T& operator*()
	{
		return component_registry<T>::m_components[m_index];
	}
};

template <typename... ComponentTypes>
class TEntity : public component_handle<ComponentTypes>...
{
public:

	~TEntity()
	{
		(remove<ComponentTypes>(), ...);
	}

	EntityHandle clone()
	{
		EntityHandle eh = Game::entity_registry->create();
		(eh->add<ComponentTypes>(), ...);
		return eh;
	}

	template<typename T, typename... TArgs>
	void add(TArgs&& ...mArgs)
	{
		static_assert(sizeof(T) >= sizeof(uint32_t));

		ASSERT(!has<T>());

		component_handle<T>::m_index = attach<T>();

	}

	template<typename T>
	inline component_handle<T> get()
	{
		ASSERT(has<T>());
		//return *static_cast<component_handle<T>*>(this);
		return { component_handle<T>::m_index }; //need to fix this, returning a member variable wasnt working
	}


	template<typename T>
	void remove()
	{
		//ASSERT(has<T>()); 

		detach<T>(component_handle<T>::m_index);

		component_handle<T>::m_index = INVALID;
	}

	template<typename T>
	inline bool has()
	{
		return !(component_handle<T>::m_index == INVALID);
	}

	bool is_active() {
		return m_Active;
	}

private:
	bool m_Active = true;
};

template <typename... ComponentTypes>
void to_json(json& j, const TEntity<ComponentTypes...>& p) 
{
	//fold expression to all component types
}
template <typename... ComponentTypes>
void from_json(const json& j, TEntity<ComponentTypes...>& p) {}