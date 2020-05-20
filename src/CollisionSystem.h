#pragma once

#include "System.h"

class CollisionSystem : public System
{
public:

	virtual bool isValid(EntityHandle eh) const override;

	virtual void update(float) override;

private:

};

#include <string>
using String1 = std::string;
using String2 = std::string;
using String3 = std::string;
using String4 = std::string;

template<typename S1, typename S2>
void foo();

template<>
void foo<String1, String2>()
{

}



/*

event system.

multimap<event, listenerentity>

mario -->
other 

//collision - AABB

//collision resolution - 
this is case by case. specific to the two entities. 

(sidenote: in most cases it is mario who is affected by the collision -- specific to smb3)

template<EntityType T1, EntityType T2>
void resolve<Goomba, Mario>()
{
	//resolve collision...
}

template<EntityType T1, EntityType T2>
void resolve<Floor, Mario>()
{
	//resolve collision...
}

//an option is to sort entities within groups
than to check whether every entity within group mario and every entity within group goomba collide. 

QuadTree

Have a quadtree where you store the position of each entity. (position could be top left corner of sprite)

Naive approach:
What does Mario collide with?

Find Mario entity within quadtree. Then go back through the tree until you reach a square of space (a node) that envelops Mario Sprite width and height.

Then check whether another entity is within that square of space (aka whether the node has any other children).

Then perform AABB collision detection with those entities.

ISSSUE WITH THIS APPROACH:
It would only check collision with top left corner of other entities, so not all collisions would be detected. 

A way to resolve this:
store all four vertices of an entity's sprite within the quad tree. 


CONS: would have to update quad tree at each frame. ->Worst case: nlogn
	  but I could update entities within quad tree only if they move. 


*/