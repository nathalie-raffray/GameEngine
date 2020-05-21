#pragma once

enum class CollisionType
{
	AABB
};

struct ColliderComponent
{
	CollisionType type;
};



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
