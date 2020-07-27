#include "EventManager.h"

#define HANDLE(event_type) \
for(auto& event : events<event_type>)\
{\
	for (auto& listener : listeners<event_type>)\
	{\
		listener->handle(event);\
	}\
}\
events<event_type>.clear();

//----------------------------------------------------------------------------------------------

void EventManager::process_events()
{
	HANDLE(static_dynamic_collision);
	HANDLE(static_triggerdynamic_collision);
	HANDLE(triggerstatic_dynamic_collision);
	HANDLE(kinematic_collision);
	HANDLE(dynamic_dynamic_collision);

	HANDLE(pause);
}

//----------------------------------------------------------------------------------------------
