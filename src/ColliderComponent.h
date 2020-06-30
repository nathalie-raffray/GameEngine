#pragma once

enum class CollisionType
{
	AABB, Static, Kinematic, Dynamic
};

struct ColliderComponent
{
	CollisionType type;
	//bool discrete_continuous collisionResolution; //only for dynamic colliders
	//Vector2 posBeforeCollision
};

struct DynamicCollider
{
	bool discrete_continuous_resolution; //only for dynamic colliders
	bool is_trigger;
	bool is_kinematic;
	//dynamic colliders are affected by gravity and physics forces unless they are kinematic, in which case
	//you control them. dynamic colliders move, unlike static colliders.
	//eg. the leaf is kinematic. leaf can go through blocks without collision resolution. same as star. mushroom is NOT kinematic though
	//since mushroom is affected by gravity and collides with blocks.

};
//https://docs.unity3d.com/Manual/CollidersOverview.html


//if trigger dynamic collider (mario) and non trigger dynamic collider (goomba) collide, trigger message will be sent to goomba and mario
struct StaticCollider //cannot move
{
	bool is_trigger; //for example a block is a static collider w/normal static/dynamic collision resolutoin that should trigger when mario hits it so that a coin pops out
};

/*
physics system which takes care of all static v dynamic collisions
eg. mario colliding with tile, then there is some collision resolution, ie. push back in opposite direction of collision

coins would be kinematic because we want the collision resolution to be specific to a coin entity
*/


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
