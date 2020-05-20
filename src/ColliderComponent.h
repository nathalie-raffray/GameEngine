#pragma once

struct ColliderComponent
{
	enum class CollisionType
	{
		AABB
	};

	CollisionType type;
};

enum EventType
{
	COLLISION
};

struct Event
{
	virtual ~Event() {}
	EventType type;
};

//public EventSystem : public CollisionSystem
/*

will have to control order of event update functions. 

*/

struct CollisionSystem : public System
{
	virtual void update(float) override
	{
		for (auto e1 : m_entities)
		{
			for (auto e2 : m_entities)
			{
				//check collision between e1 and e2

				//if collision found
				ColliderEvent event;
				event.type = COLLISION;
				event.collider1 = e1;
				event.collider2 = e2;

				EventManager::events.emplace(event.type, event);

				//EventManager::events_broadcasted.emplace(e1, event);
				//EventManager::events_broadcasted.emplace(e2, event); //it depends if e1 and e2 are listening to collision events, but I suppose once the event is processed, both will be deleted
				//the above is in efficient because now i have two keys to the same value, but value is repeated twice in memory

				//other option is to have the list of events in my event manager and then events_broadcasted value will be reference to one of those events
				//that method would allow me to have only one event (eg. GAME PAUSED, or SPACEBAR PRESSED) that all the entities could refer to

				//but systems should register to listen to events
			}
		}
	}

private:
	//Quad tree, or grid
};

//RATHER THAN THAT....HAVE A COLLISION SYSTEM WHERE ENTITIES CAN REGISTER

struct PauseEvent : public Event
{
	explicit PauseEvent(const PauseEvent&) {}
};

//using Listener = TListener<ColliderEvent, PauseEvent>;

template<typename EventType>
struct TListener
{
	virtual ~TListener() {}
	
	virtual void handle(const EventType& event) {}
};

struct Listener : public TListener<ColliderEvent>,
				  public TListener<PauseEvent>
{
	virtual ~Listener() {}

};

/*template<typename... EventTypes>
struct TListener : public EventHandler<EventTypes>...
{
	virtual ~TListener() {}

};*/

/*
struct Listener : public TListener<ColliderEvent, PauseEvent>
{

};
*/




/*
struct Listener //so the listeners will be systems
{
	enum class EventType
	{
		COLLISION
	};
	
	virtual ~Listener(){}

	virtual void handle(EventType type, const Event& event) = 0;
	virtual void handle() {

		for (auto entity : entities)
		{
			auto events = EventManager::events_broadcasted[entity];
			for (auto& e : events)
			{
				//dynamic_cast
			}
		}
	}

	template<typename EventType>
	virtual void handle() = 0;

	//std::vector<EntityHandle> entities;

};
*/


struct GoombaController :
		public System, public Listener
{
	//using Listener::~TListener<
	virtual void handle(const ColliderEvent& event) override
	{

	}

	virtual void handle(const PauseEvent& event) override
	{

	}


	//void handle<CollisionEvent>(const CollisionEvent& event) override

	//void handle<CollisionEvent, Goomba>(const CollisionEvent& event) override
	//void handle<CollisionEvent, Shell>(const CollisionEvent& event) override


};

struct ColliderEvent : public Event
{
	EntityHandle collider1;
	EntityHandle collider2;
};



#include <map>
#include <set>
struct EventManager
{
	
	//static std::multimap<EntityHandle, Event> events_broadcasted;
	//static std::multimap<Listener, Event> events_broadcasted;

	//static std::multimap<MultiKey, Event> events_broadcasted;
	static std::multimap<EventType, Listener> listeners;
	static std::multimap<EventType, Event> events;
	//static std::set<Event> events;

	static void process_events()
	{
		for (auto it_listener = listeners.lower_bound(COLLISION); it_listener != listeners.upper_bound(COLLISION); it_listener++)
		{
			for (auto it_event = events.lower_bound(COLLISION); it_event != events.upper_bound(COLLISION); it_event++)
			{
				auto event = dynamic_cast<ColliderEvent&>(it_event->second);
				it_listener->second.handle(event);
			}
		}
	}

	static void add_listener(EventType type, const Listener& listener)
	{
		listeners.emplace(type, listener);
	}

};

struct Hihi
{
	/*
		associate event system to inputs

		collision system detects collision and broadcasts event


		maybe through a system of grids
		(first start with O(n^2) algorithm)

		multimap<entityhandle, event> EventMap

		register to listen to an event type
		multimap<event, listener>

		update(CollisionSystem), then the rest.
		beginning of frame delete multimap, then fill it again.

		within marioController system:
		if(Event e = EventMap[entityhandle])
		{
			switch(e.collider2.name)
			{
				case "goomba":
					break;
			}
		}

		

		bool Jump(){return isSpaceDown() || isAPressed();} DATA DRIVEN???

		ActionSystem

		actionstate<ActionName, ActionValue>
		actionmap<ActionName, Input>
		update actionstate every frame

		ActionValue getActionValue(ActionNAme){}

		class BRAIN()
		{
			virtual getActionValue(Action){}
		}

		class GOOMBABRAIN()
		{

		}

		class AISystem : public GOOMBRABRAIN
		{

		}

		void jump()
		{
			if(AIsYTEM::getActionValue(Jump))
			{
				transform.position.y +=1;
			}
		}

		system: mariocontroller
		
		*/
};