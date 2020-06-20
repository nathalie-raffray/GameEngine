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
}


