#include "Game.h"

namespace GM
{
	Entity::Entity() : x(0), y(0), id(0)
	{}
	Entity::Entity(uint8_t _id) : x(0), y(0), id(_id)
	{}
	Entity::Entity(uint16_t _x, uint16_t _y) : x(_x), y(_y), id(0)
	{}
	Entity::Entity(uint8_t _id, uint16_t _x, uint16_t _y) : x(_x), y(_y), id(_id)
	{}

	uint8_t Entity::getId() { return id; }
	void Entity::setPoint(uint16_t _x, uint16_t _y) { x = _x; y = _y; }
}