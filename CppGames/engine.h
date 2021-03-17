#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <unordered_map>
#include <iostream>

namespace SDL
{
	const struct Color
	{
		static constexpr SDL_Color
			White = { 255,255,255,255 },
			Black = { 0,0,0,0 },
			Red = { 255, 0, 0, 255 },
			Blue = { 0,0,255,255 },
			Green = { 0,255,0,255 };
	};

	struct textureData
	{
		SDL_Texture* texture;
		const uint16_t width;
		const uint16_t height;
		uint8_t index;
	};

	class KeyboardEventHandler
	{
	private:
		std::unordered_map<SDL_KeyCode, bool> keyStates;

	public:
		

		void handleKeyboardEvent(SDL_KeyboardEvent e) 
		{
			keyStates[(SDL_KeyCode) e.keysym.sym] = (e.state == SDL_PRESSED);
		}

		bool isPressed(SDL_KeyCode keyCode) 
		{
			return (keyStates[keyCode] == SDL_PRESSED);
		}

		bool isReleased(SDL_KeyCode keyCode) 
		{
			return (keyStates[keyCode] == SDL_RELEASED);
		}
	};

	class Engine
	{
	private:
		bool isRunning;

		uint16_t width;
		uint16_t height;
		uint16_t spriteIndex;

		TTF_Font* currentFont;

		std::vector<SDL_Texture*> textures;
		std::vector<SDL_Surface*> surfaces;

		SDL_Window* window;
		SDL_Renderer* renderer;

	protected:
		std::vector<textureData> allTextData;

	public:
		// setup
		void init(const char* title, uint16_t xpos, uint16_t ypos, uint16_t _width, uint16_t _height, bool fullscreen);
		void init_ttf();

		// create textures
		textureData createTextSprite(const char* content, SDL_Color color);
		textureData createTextSpriteWrapped(const char* content, SDL_Color color);
		textureData createTextSprite(const char* content, SDL_Color fgColor, SDL_Color bgColor);
		SDL_Texture* createSprite(const char* file);

		// render textures
		void renderSprite(SDL_Texture* texture);
		void renderSprite(SDL_Texture* texture, uint16_t dest_x, uint16_t dest_y, uint16_t size);
		void renderSprite(SDL_Texture* texture, uint16_t dest_x, uint16_t dest_y, uint16_t width, uint16_t height);
		void renderSprite(SDL_Texture* texture, uint16_t src_x, uint16_t src_y, uint16_t dest_x, uint16_t dest_y, uint16_t shapeSize);
		void renderSprite(SDL_Texture* texture, uint16_t src_x, uint16_t src_y, uint16_t dest_x, uint16_t dest_y, uint16_t shapeSize, float scale);

		// basic draw methods
		void setDrawColor(SDL_Color color);
		void drawPixel(uint16_t x, uint16_t y);
		void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

		// updates and cleaning
		void showScreen();
		void clearScreen();
		void clearSprites();
		void clearSpriteIndex(int index);
		void clean();
		void clean_ttf();

		// getters/setters
		SDL_Event getEvents();
		bool running();
		int getWidth();
		int getHeight();
	};
}