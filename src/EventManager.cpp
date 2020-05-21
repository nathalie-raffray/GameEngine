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

void EventManager::process_events()
{
	HANDLE(ColliderEvent);
	HANDLE(PauseEvent);
	/*for (auto event : events<ColliderEvent>)
	{
		for (auto& listener : listeners<ColliderEvent>)
		{
			listener->handle(event);
		}
	}
	events<ColliderEvent>.clear();*/
}
