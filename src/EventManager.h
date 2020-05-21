#pragma once
#include <set>
#include <vector>
#include <algorithm>

#include "Listener.h"

#include "ColliderEvent.h"
#include "PauseEvent.h"

class EventManager
{
public:
	template<typename T>
	static inline std::vector<Listener<T>*> listeners;

	template<typename T>
	static inline std::set<T> events;

	static void process_events();

	template<typename T>
	static void add_listener(Listener<T>* listener)
	{
		listeners<T>.emplace_back(listener);
	}

	template<typename T>
	static void remove_listener(Listener<T>* listener)
	{
		listeners<T>.erase(std::find(listeners<T>.begin(), listeners<T>.end(), listener));
	}

};

template<typename T>
inline std::vector<Listener<T>*> EventManager::listeners = {};

template<typename T>
inline std::set<T> EventManager::events = {};
