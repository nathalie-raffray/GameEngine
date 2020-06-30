#include "GoombaController.h"
#include <iostream>

bool GoombaController::isValid(EntityHandle eh) const
{
	return eh->has<ColliderComponent>();
}

void GoombaController::update(float dt)
{

}

void GoombaController::handle(const ColliderEvent& event) 
{
	//if(event.collider1 belong to m_entites && event.collider2.is_active())
	//else if(event.collider2 belong to m_entities && event.collider1.is_active())
	
	//std::cout << "collider 1 : " << event.collider1.m_index << std::endl;
	//std::cout << "collider 2 : " << event.collider2.m_index << std::endl;

//	std::cout << "handled" << std::endl;

	//this is to handle DynamicDynamicCollision 

	//if one entity has playercomponent and the other has goombacomponent
	//check if player y is above goomba y
	//then goomba health decreases (if greater than 1)
	//maybe another system maybe takes care of playing death animation then removing goomba if health is 0
	
	//if one entity is goomba and the other is shell
	//then goomba health decreases

	//else if one or two entities is goomba 
	//then change direction goomba was walking in
}


