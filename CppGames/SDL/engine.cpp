#include "engine.h"

namespace SDL
{
	/// <summary>
	/// Initialises the SDL window and renderer, along with other backend stuff.
	/// </summary>
	/// <param name="title">The title of the window</param>
	/// <param name="xpos">the x position of the window</param>
	/// <param name="ypos">the y position of the window</param>
	/// <param name="width">the width of the window</param>
	/// <param name="height">the height of the window</param>
	/// <param name="fullscreen">whether or not the window is fullscreen</param>
	void inline Engine::init(const char* title, uint16_t xpos, uint16_t ypos, uint16_t _width, uint16_t _height, bool fullscreen)
	{
		spriteIndex = 0;
		width = _width;
		height = _height;

		int flags;

		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
		}
		else
		{
			flags = SDL_WINDOW_OPENGL;
		}


		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			std::cout << "SDL failed to initialise! SDL Error: " << SDL_GetError() << std::endl;
			isRunning = false;
		}
		else
		{
			std::cout << "Successful initialisation!" << std::endl;

			window = SDL_CreateWindow(title, xpos, ypos, _width, _height, flags);
			if (window)
			{
				std::cout << "Window Created" << std::endl;
			}

			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				std::cout << "Renderer Created" << std::endl;
			}

			isRunning = true;
		}
	}

	void Engine::init_ttf()
	{
		TTF_Init();
		currentFont = TTF_OpenFont("./assets/raleway/Raleway-Light.ttf", 25);
		if (currentFont == NULL) std::cout << TTF_GetError() << std::endl;
	}

	// texture stuff

	void Engine::createTextSprite(const char* content, SDL_Color color)
	{
		SDL_Surface* surface = TTF_RenderUTF8_Blended(currentFont, content, color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (surface)
		{
			std::cout << "Surface Successfully Loaded!" << std::endl;

			if (texture)
			{
				std::cout << "Texture Successfully Loaded!" << std::endl;
				textures.push_back(texture);
				surfaces.push_back(surface);
				allTextureData.push_back({ texture, (uint16_t)surface->w, (uint16_t)surface->h, spriteIndex++ });
			}
			else
			{
				SDL_FreeSurface(surface);
				std::cout << "Texture Failed to Load: " << SDL_GetError() << std::endl;
			}
		}
		else
		{
			std::cout << "Surface Failed to Load: " << SDL_GetError() << std::endl;
		}
	}

	void Engine::createTextSpriteWrapped(const char* content, SDL_Color color)
	{
		SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(currentFont, content, color, Engine::width / 2);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (surface)
		{
			std::cout << "Surface Successfully Loaded!" << std::endl;

			if (texture)
			{
				std::cout << "Texture Successfully Loaded!" << std::endl;
				textures.push_back(texture);
				surfaces.push_back(surface);
				allTextureData.push_back({ texture, (uint16_t)surface->w, (uint16_t)surface->h, spriteIndex++ });
			}
			else
			{
				SDL_FreeSurface(surface);
				std::cout << "Texture Failed to Load: " << SDL_GetError() << std::endl;
			}
		}
		else
		{
			std::cout << "Surface Failed to Load: " << SDL_GetError() << std::endl;
		}
	}

	void Engine::createTextSprite(const char* content, SDL_Color fgColor, SDL_Color bgColor)
	{
		SDL_Surface* surface = TTF_RenderText_Shaded(currentFont, content, fgColor, bgColor);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (surface)
		{
			std::cout << "Surface Successfully Loaded!" << std::endl;

			if (texture)
			{
				std::cout << "Texture Successfully Loaded!" << std::endl;
				textures.push_back(texture);
				surfaces.push_back(surface);
				allTextureData.push_back({ texture, (uint16_t)surface->w, (uint16_t)surface->h, spriteIndex++ });
			}
			else
			{
				SDL_FreeSurface(surface);
				std::cout << "Texture Failed to Load: " << SDL_GetError() << std::endl;
			}
		}
		else
		{
			std::cout << "Surface Failed to Load: " << SDL_GetError() << std::endl;
		}
	}

	/// <summary>
	/// Retrieves, from a file, the img as a SDL_Texture*.
	/// </summary>
	/// <param name="file">file name</param>
	/// <returns>image as an SDL_Texture*</returns>
	void Engine::createSprite(const char* file)
	{
		SDL_Surface* surface = SDL_LoadBMP(file);
		if (surface)
		{
			std::cout << "Surface Successfully Loaded!" << std::endl;
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

			if (texture)
			{
				std::cout << "Texture Successfully Loaded!" << std::endl;
				textures.push_back(texture);
				surfaces.push_back(surface);
				allTextureData.push_back({ texture, (uint16_t)surface->w, (uint16_t)surface->h, spriteIndex++ });
			}
			else
			{
				SDL_FreeSurface(surface);
				std::cout << "Texture Failed to Load: " << SDL_GetError() << std::endl;
			}
		}
		else
		{
			std::cout << "Surface Failed to Load: " << SDL_GetError() << std::endl;
		}
	}

	/// <summary>
	/// Renders the given SDL_Texture*.
	/// </summary>
	/// <param name="texture">The SDL_Texture* to render</param>
	void Engine::renderSprite(SDL_Texture* texture)
	{
		SDL_RenderCopy(renderer, texture, NULL, NULL);
	}

	void Engine::renderSprite(SDL_Texture* texture, uint16_t dest_x, uint16_t dest_y, uint16_t size)
	{
		SDL_Rect DestR;

		DestR.x = dest_x;
		DestR.y = dest_y;
		DestR.w = size;
		DestR.h = size;

		SDL_RenderCopy(renderer, texture, NULL, &DestR);
	}

	void Engine::renderSprite(SDL_Texture* texture, uint16_t dest_x, uint16_t dest_y, uint16_t width, uint16_t height)
	{
		SDL_Rect DestR;

		DestR.x = dest_x;
		DestR.y = dest_y;
		DestR.w = width;
		DestR.h = height;

		SDL_RenderCopy(renderer, texture, NULL, &DestR);
	}

	/// <summary>
	/// Renders the given SDL_Texture*, but allows clipping (for a sprite sheet).
	/// </summary>
	/// <param name="texture">The SDL_Texture* to render</param>
	/// <param name="src_x">sprite x location in image</param>
	/// <param name="src_y">sprite y location in image</param>
	/// <param name="dest_x">x location of where to draw the sprite</param>
	/// <param name="dest_y">y location of where to draw the sprite</param>
	/// <param name="shapeSize">the size of the shape (assumes its a square)</param>
	void Engine::renderSprite(SDL_Texture* texture, uint16_t src_x, uint16_t src_y, uint16_t dest_x, uint16_t dest_y, uint16_t shapeSize)
	{
		SDL_Rect SrcR;
		SDL_Rect DestR;

		SrcR.x = src_x;
		SrcR.y = src_y;
		SrcR.w = shapeSize;
		SrcR.h = shapeSize;

		DestR.x = dest_x;
		DestR.y = dest_y;
		DestR.w = shapeSize;
		DestR.h = shapeSize;

		SDL_RenderCopy(renderer, texture, &SrcR, &DestR);
	}

	/// <summary>
	/// Renders the given SDL_Texture*, but allows clipping (for a sprite sheet).
	/// </summary>
	/// <param name="texture">The SDL_Texture* to render</param>
	/// <param name="src_x">sprite x location in image</param>
	/// <param name="src_y">sprite y location in image</param>
	/// <param name="dest_x">x location of where to draw the sprite</param>
	/// <param name="dest_y">y location of where to draw the sprite</param>
	/// <param name="shapeSize">the size of the shape (assumes its a square)</param>
	void Engine::renderSprite(SDL_Texture* texture, uint16_t src_x, uint16_t src_y, uint16_t dest_x, uint16_t dest_y, uint16_t shapeSize, float scale)
	{
		SDL_Rect SrcR;
		SDL_Rect DestR;

		SrcR.x = src_x;
		SrcR.y = src_y;
		SrcR.w = shapeSize;
		SrcR.h = shapeSize;

		DestR.x = dest_x;
		DestR.y = dest_y;
		DestR.w = (int)round(shapeSize * scale);
		DestR.h = (int)round(shapeSize * scale);

		SDL_RenderCopy(renderer, texture, &SrcR, &DestR);
	}

	void Engine::setDrawColor(SDL_Color color)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	}

	void Engine::drawPixel(uint16_t x, uint16_t y)
	{
		SDL_RenderDrawPoint(renderer, x, y);
	}

	void Engine::drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
	{
		SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
	}

	// update
	SDL_Event Engine::getEvents()
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		return event;
	}

	void Engine::showScreen()
	{
		SDL_RenderPresent(renderer);
	}

	void Engine::clearScreen()
	{
		SDL_RenderClear(renderer);
	}

	void Engine::clearSprites()
	{
		#pragma omp parallel sections 
		{
			#pragma omp section
			{
				for (SDL_Texture* texture : textures)
				{
					SDL_DestroyTexture(texture);
				}
				textures.clear();
			}

			#pragma omp section
			{
				for (SDL_Surface* surface : surfaces)
				{
					SDL_FreeSurface(surface);
				}
				surfaces.clear();
			}
		}

		spriteIndex = 0;
	}

	void Engine::clearSpriteIndex(int index)
	{
		SDL_DestroyTexture(textures[index]);
		SDL_FreeSurface(surfaces[index]);
		textures.erase(textures.begin() + index);
		surfaces.erase(surfaces.begin() + index);
		--spriteIndex;

		#pragma omp parallel for
		for (int i = 0; i < allTextureData.size(); ++i)
		{
			allTextureData[i].index = i;
		}
	}

	void Engine::clean()
	{
		#pragma omp parallel sections 
		{
			#pragma omp section
			{
				for (SDL_Texture* texture : textures)
				{
					SDL_DestroyTexture(texture);
				}
				textures.clear();
			}

			#pragma omp section
			{
				for (SDL_Surface* surface : surfaces)
				{
					SDL_FreeSurface(surface);
				}
				surfaces.clear();
			}
		}

		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}

	void Engine::clean_ttf()
	{
		TTF_CloseFont(currentFont);
		TTF_Quit();
	}

	// getters/setters
	bool Engine::running() { return isRunning; }
	int Engine::getWidth() { return width; }
	int Engine::getHeight() { return height; }
}