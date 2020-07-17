#pragma once

/*
enum class collision_type
{
	Static, Kinematic, Dynamic
};
*/

struct ColliderComponent
{
	bool is_trigger;
	//bool discrete_continuous_resolution; //only for dynamic colliders
	bool padding[3];

	static inline const char* name = "collider component"; 
	//collision_type type;
};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const ColliderComponent& c)
{
	j["is_trigger"] = c.is_trigger;
	//j["discrete_continuous_resolution"] = c.discrete_continuous_resolution;
	/*if (c.type != collision_type::Static)
	{
		j["discrete_continuous_resolution"] = c.discrete_continuous_resolution;
	}*/
}
inline void from_json(const json& j, ColliderComponent& c)
{
	TRY_PARSE_ELSE(c.is_trigger = j.at("is_trigger"), c.is_trigger = false);
	//TRY_PARSE_ELSE(c.discrete_continuous_resolution = j.at("discrete_continuous_resolution"), c.discrete_continuous_resolution = false);
	//c.type = collision_type::Static;
}

/*
struct DynamicCollider
{
	bool discrete_continuous_resolution; //only for dynamic colliders
	bool is_trigger;

	//bool is_kinematic;
	//dynamic colliders are affected by gravity and physics forces unless they are kinematic, in which case
	//you control them. dynamic colliders move, unlike static colliders.
	//eg. the leaf is kinematic. leaf can go through blocks without collision resolution. same as star. mushroom is NOT kinematic though
	//since mushroom is affected by gravity and collides with blocks.

};*/
//https://docs.unity3d.com/Manual/CollidersOverview.html


//if trigger dynamic collider (mario) and non trigger dynamic collider (goomba) collide, trigger message will be sent to goomba and mario

/*
UNITY STATIC:
A static collider is a GameObject that has a Collider but no Rigidbody. Static colliders are
mostly used for level geometry which always stays at the same place and never moves around.
Incoming Rigidbody objects collide with static colliders but don’t move them.
*/
/*
struct StaticCollider //cannot move
{
	bool is_trigger; //for example a block is a static collider w/normal static/dynamic collision resolutoin that should trigger when mario hits it so that a coin pops out
};

struct ColliderComponent
{
	CollisionType type; //is this necessary? we know a collider is static if entity has no rigidbody
						//and we know it's
	union collider
	{
		DynamicCollider dynamic_collider;
		StaticCollider static_collider;
	};
	//bool discrete_continuous collisionResolution; //only for dynamic colliders
	//Vector2 posBeforeCollision 
};
*/

/*
struct collidercomp
{
	/*
	the most basic collider component: 
	we know collider is static if entity has no rigidbody attached.
	otherwise dynamic collider. its a dynamic kinematic collider if is_kinematic is true. 
	however, collidercomponent above is a more descriptive intuitive way to structure it. 
	with padding collidercomp is 4bytes.
	so could add bool static_dynamic.
	*//* 
	bool discrete_continuous_resolution; 
	bool is_trigger;
	bool is_kinematic;
};

*/

/*
physics system which takes care of all static non-trigger v dynamic non-kinematic non-trigger collisions
eg. mario colliding with tile, then there is some collision resolution, ie. push back in opposite direction of collision

collision system which sends the collision events. 



coins would be kinematic because we want the collision resolution to be specific to a coin entity.
or, coins would be static with is_trigger=true, since coins don't have rigidbodies. 

UNITY KINEMATIC DYNAMIC:
according to Unity: You can move a kinematic rigidbody object from a script by modifying its Transform Component
but it will not respond to collisions and forces like a non-kinematic rigidbody. Kinematic rigidbodies should be used for colliders 
that can be moved or disabled/enabled occasionally but that should otherwise behave like static colliders

mario should collide with static colliders. so dynamic non trigger non kinematic. 
mario should collide with kinematic dynamic colliders. (collision response is only to mario). 
an enemy could have a kinematic dynamic collider...? (note, kinematic can be turned on and off) 

coins can't be moved. so should be static.
leaf can be moved. so dynamic kinematic trigger. 

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
