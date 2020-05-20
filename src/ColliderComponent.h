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
	//explicit PauseEvent(const PauseEvent&) {}
};

//using Listener = TListener<ColliderEvent, PauseEvent>;

struct BListener
{
	virtual ~BListener() {}

	template<typename EventType>
	void handle(const EventType& event);

};

struct DListener : public BListener
{
	template <typename EventType>
	void handle(const EventType& event)
	{
		BListener::handle<EventType>(event);
	}


};

template<>
void DListener::handle<ColliderEvent>(const ColliderEvent& event)
{
	
}

template<>
void DListener::handle<PauseEvent>(const PauseEvent& event)
{

}


template<typename T>
struct Listener
{
	Listener()
	{
		EventManager::add_listener<T>(*this);
	}
	
	virtual ~Listener() {}
	virtual void handle(const T& event);
};

struct GoombaController : public System, public Listener<ColliderEvent>
{
	void handle(const ColliderEvent& event) override
	{

	}
};

struct ColliderEvent : public Event
{
	EntityHandle collider1;
	EntityHandle collider2;

	// ColliderEvent(const ColliderEvent& event) {}
	// ColliderEvent(const PauseEvent& event) = delete;

};



#include <map>
#include <set>
struct EventManager
{
	template<typename T>
	static std::set<Listener<T>&> listeners; //eg. T = Listener<ColliderEvent>

	template<typename EventType>
	static std::set<EventType> events;

	//static std::multimap<EventType, DListener> listeners;
	//static std::multimap<EventType, Event> events;

	static void process_events()
	{
		for(auto event : events<ColliderEvent>)
		{
			for (auto listener : listeners<ColliderEvent>)
			{
				listener.handle(event);
			}
		}
	}

	template<typename T>
	static void add_listener(const Listener<T>& listener)
	{
		listeners<Listener<T>>.insert(listener);
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