#include "ColliderEvent.h"

bool ColliderEvent::operator<(const ColliderEvent& event) const
{
	if (collider1.m_index < event.collider1.m_index)
	{
		return true;
	}
	if (collider1.m_index > event.collider1.m_index)
	{
		return false;
	}
	if (collider2.m_index < event.collider2.m_index)
	{
		return true;
	}
	if (collider2.m_index > event.collider2.m_index)
	{
		return false;
	}
	return false;
}