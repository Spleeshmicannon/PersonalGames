#pragma once
#include "engine.h"

namespace GM
{
	class Entity
	{
	protected:
		const uint8_t id;

	public:
		uint16_t x, y;

		Entity();
		Entity(uint8_t _id);
		Entity(uint16_t _x, uint16_t _y);
		Entity(uint8_t _id, uint16_t _x, uint16_t _y);

		uint8_t getId();
		void setPoint(uint16_t _x, uint16_t _y);
	};

	class Game
	{
	private:

	protected:
		SDL::KeyboardEventHandler keyboardEventHandler;

	public:
		virtual void setup();
		virtual bool update();
		virtual void clean();
	};
}