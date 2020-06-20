#pragma once
#include <vector>
#include <stack>

constexpr uint32_t INVALID = ~0u;

template<typename ComponentType>
struct component_registry
{
	static std::vector<ComponentType> m_components;
	//inline static uint32_t m_freeIndex = INVALID; //m_freeIndex was giving me difficulties at the end of the program, since my components are not pure data
	static std::stack<uint32_t> freeIndices;
};

template<typename ComponentType>
std::vector<ComponentType> component_registry<ComponentType>::m_components = { };

template<typename ComponentType>
std::stack<uint32_t> component_registry<ComponentType>::freeIndices({ INVALID });


template<typename T>
void detach(uint32_t index)
{
	if (index == INVALID) return;

	component_registry<T>::freeIndices.push(index);

	/*auto* pNextFree = &component_registry<T>::m_freeIndex;
	while (*pNextFree != -1)
	{
		pNextFree = reinterpret_cast<uint32_t*>(&component_registry<T>::m_components[*pNextFree]);
	}
	*pNextFree = index;
	*reinterpret_cast<uint32_t*>(&component_registry<T>::m_components[index]) = INVALID;*/
}

template<typename T>
uint32_t attach()
{
	//auto& index = component_registry<T>::m_freeIndex;
	const auto& index = component_registry<T>::freeIndices.top();

	if (index == -1)
	{
		//component_registry::m_components<T>.emplace_back(std::forward<TArgs>(mArgs)...);
		component_registry<T>::m_components.emplace_back();

		return static_cast<uint32_t>(component_registry<T>::m_components.size()) - 1;
	}
	else
	{
		/*auto indexCopy = index;
		index = *reinterpret_cast<uint32_t*>(&component_registry<T>::m_components[index]);
		component_registry<T>::m_components[indexCopy] = { };
		return indexCopy; */

		component_registry<T>::m_components[index] = { };
		component_registry<T>::freeIndices.pop();

		return index;
	}
}