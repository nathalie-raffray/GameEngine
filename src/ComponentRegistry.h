#pragma once
//#include <vector>

template<typename ComponentType>
struct ComponentRegistry
{
	static std::vector<ComponentType> components;

};
//definition of a non-template data member of a class template
template<typename ComponentType>
std::vector<ComponentType> ComponentRegistry<ComponentType>::components = {};
/*
Since it is part of a template, as with all templates the compiler will make sure
it's only defined once.
*/

template<typename T>
struct ComponentHandle //PLAIN OLD DATA STRUCTURE
{
	std::size_t m_Handle;

	T* operator->()
	{
		return &ComponentRegistry<T>::components[m_Handle];
	}
	T& operator*()
	{
		return ComponentRegistry<T>::components[m_Handle];
	}
};