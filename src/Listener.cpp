#include "EventManager.h"

template<typename T>
Listener<T>::Listener()
{
	activate();
}

template<typename T>
Listener<T>::~Listener()
{
	deactivate();
}

template<typename T>
void Listener<T>::activate()
{
	EventManager::add_listener<T>(this);
}

template<typename T>
void Listener<T>::deactivate()
{
	EventManager::remove_listener<T>(this);
}

//----------------------------------------------------------------------------------------------
/*  LISTENER TEMPLATE CLASS DECLARATIONS */ //(put this in Listener.cpp to avoid slower compilation due to duplicate implementations)

template struct Listener<pause>;

//COLLISION EVENTS:
template struct Listener<static_dynamic_collision>;
template struct Listener<static_triggerdynamic_collision>;
template struct Listener<triggerstatic_dynamic_collision>;
template struct Listener<kinematic_collision>;
template struct Listener<dynamic_dynamic_collision>;