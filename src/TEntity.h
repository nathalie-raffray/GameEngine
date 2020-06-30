#pragma once
#include <string>

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

	TEntity() {}

	~TEntity() {}

	void destroy()
	{
		(remove<ComponentTypes>(), ...);
	}

	void clone(TEntity* eh)
	{
		(clone<ComponentTypes>(eh), ...);
	}

	template<typename T, typename... TArgs>
	void add(TArgs&& ...mArgs)
	{
		static_assert(sizeof(T) >= sizeof(uint32_t));

		ASSERT(!has<T>());

		component_handle<T>::m_index = attach<T>();

	}

	template<typename T>
	inline component_handle<T> get() const
	{
		ASSERT(has<T>());
		//return *static_cast<component_handle<T>*>(this);
		return { component_handle<T>::m_index }; 
	}


	template<typename T>
	void remove()
	{
		//ASSERT(has<T>()); 
		detach<T>(component_handle<T>::m_index);

		component_handle<T>::m_index = INVALID;
	}

	template<typename T>
	inline bool has() const
	{
		return !(component_handle<T>::m_index == INVALID);
	}

	bool is_active() {
		return m_Active;
	}

	/*CALL ONCE AT THE BEGINNING OF EACH LEVEL*/
	/*static void clear_component_registry()
	{
		(m_components<ComponentTypes>().clear(), ...);
		(freeIndices<ComponentTypes>().clear(), ...);
		(freeIndices<ComponentTypes>().push(INVALID), ...);
	}*/

private:

	template<typename T>
	void clone(TEntity* eh)
	{
		if (this->has<T>()) {
			if(!eh->has<T>())
			{
				eh->add<T>();
			}
			*eh->get<T>() = *this->get<T>();
		}
	}

private:
	bool m_Active = true;
};


/*
#include "json_serialization.h"

template <typename... ComponentTypes>
void to_json(json& j, const TEntity<ComponentTypes...>& p) 
{
	/*if (p.has<AssetComponent>())
	{
		EntityAsset* ea = Game::assets->get<EntityAsset>(p.get<AssetComponent>().entity_asset_id);
		(component_to_json<ComponentTypes>(j, p.get<ComponentTypes>(), ea->entity_programmable->has<ComponentTypes>()), ...);
	}
	else {
		(component_to_json<ComponentTypes>(j, p.get<ComponentTypes>(), p.has<ComponentTypes>()), ...);
	}*/
/*}
template<typename Component>
void component_to_json(json& j, component_handle<Component> component, bool programmable)
{
	//if (component.m_index != INVALID && programmable)
	/*if(programmable)
	{
		j.push_back(*component);
		//maybe take out j["components"]
	}*/
/*}

template <typename... ComponentTypes>
void from_json(const json& j, TEntity<ComponentTypes...>& p) 
{
	/*for (auto& jj : j.items())
	{
		auto& addComponent = ComponentFactory::add_component_map[jj.key()];//do something if this fails, assert
		addComponent({ p.m_index });
		auto& from_jsonComponent = ComponentFactory::json_component_map[jj.key()];
		from_jsonComponent(jj, { p.m_index });

		if (jj.key() == "AssetComponent")
		{
			EntityAsset* ea = Game::assets->get<EntityAsset>(p.get<AssetComponent>().entity_asset_id);
			ea->entity_immutable->clone({ p.m_index });
			ea->entity_programmable->clone({ p.m_index });
		}
	}*/
//}
//}


