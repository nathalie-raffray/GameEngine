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

	void clone(TEntity* eh) const
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

public:
	bool m_Active = true;

private:

	template<typename T>
	void clone(TEntity* eh) const
	{
		if (this->has<T>()) {
			if(!eh->has<T>())
			{
				eh->add<T>();
			}
			*eh->get<T>() = *this->get<T>();
		}
	}
};




