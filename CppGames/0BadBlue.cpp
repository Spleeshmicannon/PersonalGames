// olcApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <chrono>

#define WALL_SIZE 5
#define WALL_POINTS 2
#define ENEMY_AMOUNT 7

class PixelEngine : public olc::PixelGameEngine
{
public:
	PixelEngine()
	{
		// Name you application
		sAppName = "BadBlue";
	}

private:
	// structs and globals
	struct point {
		int32_t x;
		int32_t y;
	};

	struct direction {
		bool w;
		bool a;
		bool s;
		bool d;
	};

	struct pointBool {
		bool y;
		bool x;
	};

	struct enemyData {
		point pt;
		pointBool check;
	};

	struct point player;
	struct point exit;
	struct enemyData enemy[ENEMY_AMOUNT];
	struct point walls[WALL_SIZE][WALL_POINTS];
	bool lose;


	// functions
	void DrawSquare(int32_t x, int32_t y, int length, int height, olc::Pixel pixel) 
	{
		for (int i = 0; i < length; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				Draw(x + i, y + j, pixel);
			}
		}

	}

	void DrawSquare(int32_t x, int32_t y, int length, int height) 
	{
		for (int i = 0; i < length; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				Draw(x + i, y + j, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
			}
		}

	}

	void DrawSquare(int32_t x, int32_t y, int length, int height, int max)
	{
		for (int i = 0; i < length; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				Draw(x + i, y + j, olc::Pixel(rand() % max, rand() % max, rand() % max));
			}
		}

	}

	direction collisionCheck(int32_t x, int32_t y, int size)
	{
		direction d = { true, true, true, true };

		for (int i = 0; i < size; ++i)
		{
			if (olc::WHITE == GetPixel(x + i, y - 1)) d.w = false;
		}

		for (int i = 0; i < size; ++i)
		{
			if (olc::WHITE == GetPixel(x - 1, y + i)) d.a = false;
		}

		for (int i = 0; i < size; ++i)
		{
			if (olc::WHITE == GetPixel(x + i, y + size)) d.s = false;
		}

		for (int i = 0; i < size; ++i)
		{
			if (olc::WHITE == GetPixel(x + size, y + i)) d.d = false;
		}

		return d;
	}

	bool collisionCheck(point p1, point p2, int size1, int size2)
	{
		for (int i = 0; i < size1; ++i)
		{
			for (int j = 0; j < size2; ++j)
			{
				if ((p1.x + i == p2.x + j) && (p1.y + i == p2.y + j)) return true;
			}
		}

		return false;
	}
	
	// procedures
	void KeyboardInput() 
	{
		unsigned long time = std::chrono::high_resolution_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
		time = (time - (time / 15000000000000000000));	
		
		direction d = collisionCheck(player.x, player.y, 10);

		if (d.w)
		{
			if (GetKey(olc::W).bPressed)
			{
				player.y--;
			}
			else if (GetKey(olc::W).bHeld && (time % 10 == 0))
			{
				player.y--;
			}
		}

		if (d.a)
		{
			if (GetKey(olc::A).bPressed)
			{
				player.x--;
			}
			else if (GetKey(olc::A).bHeld && (time % 10 == 0))
			{
				player.x--;
			}
		}

		if (d.s)
		{
			if (GetKey(olc::S).bPressed)
			{
				player.y++;
			}
			else if (GetKey(olc::S).bHeld && (time % 10 == 0))
			{
				player.y++;
			}
		}

		if (d.d)
		{
			if (GetKey(olc::D).bPressed)
			{
				player.x++;
			}
			else if (GetKey(olc::D).bHeld && (time % 10 == 0))
			{
				player.x++;
			}
		}

		if (GetKey(olc::R).bReleased)
		{
			setup();
		}
	}

	void MoveEnemy(enemyData &ed)
	{
		direction d = collisionCheck(ed.pt.x, ed.pt.y, 4);

		unsigned long time = std::chrono::high_resolution_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
		time = (time - (time / 15000000000000000000));

		if (!d.a)
		{
			ed.check.x = true;
		}
		
		if (!d.s)
		{
			ed.check.x = false;
		}

		if (!d.w)
		{
			ed.check.y = true;
		}

		if (!d.s)
		{
			ed.check.y = false;
		}

		if (time % 10 == 0)
		{
			if (ed.check.x)
			{
				ed.pt.x++;
			}
			else
			{
				ed.pt.x--;
			}

			if (ed.check.y)
			{
				ed.pt.y++;
			}
			else
			{
				ed.pt.y--;
			}
			
		}
	}

	void setup()
	{
		srand((unsigned)time(0));

		lose = false;

		player = { (int32_t)std::round(ScreenWidth() / 2), (int32_t)std::round(ScreenHeight() / 2) };

		for (int i = 0; i < ENEMY_AMOUNT; ++i)
		{
			enemy[i] = { { (int32_t)std::round(rand() % ScreenWidth()), (int32_t)std::round(rand() % (ScreenHeight() - 40)) }, { true, true } };
		}

		exit = { (int32_t)enemy[rand() % ENEMY_AMOUNT].pt.x, (int32_t)enemy[rand() % ENEMY_AMOUNT].pt.y };

		for (int i = 0; i < WALL_SIZE; ++i)
		{
			for (int j = 0; j < WALL_POINTS; ++j)
			{
				walls[i][j].x = rand() % ScreenWidth() + 1;
				walls[i][j].y = rand() % ScreenHeight() + 20;
			}
		}
	}

	void DrawWalls()
	{
		for (int i = 0; i < WALL_SIZE; ++i)
		{
			DrawLine(walls[i][0].x, walls[i][0].y, walls[i][1].x, walls[i][1].y, olc::WHITE);
		}

		DrawLine(0, 0, 0, ScreenHeight(), olc::WHITE);
		DrawLine(ScreenWidth() - 1, 0, ScreenWidth() - 1, ScreenHeight(), olc::WHITE);
		DrawLine(0, ScreenHeight() - 1, ScreenWidth(), ScreenHeight() - 1, olc::WHITE);
		DrawLine(0, 20, ScreenWidth(), 20, olc::WHITE);
		DrawLine(0, 0, ScreenWidth(), 0, olc::WHITE);
	}

	void DrawAll()
	{
		DrawWalls();
		DrawSquare(player.x, player.y, 10, 10);
		DrawSquare(exit.x, exit.y, 5, 5, olc::Pixel(rand() % 255, rand() % 255, 255));

		for(int i = 0; i < ENEMY_AMOUNT; ++i) DrawSquare(enemy[i].pt.x, enemy[i].pt.y, 4, 4, olc::Pixel(200, 255, 255));
	}

	void gameLoop()
	{
		KeyboardInput();
		for (int i = 0; i < ENEMY_AMOUNT; ++i)
		{
			MoveEnemy(enemy[i]);
			if (collisionCheck(enemy[i].pt, player, 4, 10)) lose = true;
		}

		if(collisionCheck(player, exit, 10, 5)) setup();
		
		Clear(olc::Pixel(256, 256, 256));
		DrawAll();
	}

public:
	bool OnUserCreate() override
	{
		setup();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if(!lose) gameLoop();
		else
		{
			Clear(olc::Pixel(256, 256, 256));
			if (GetKey(olc::R).bReleased) setup();
			for (int x = 0; x < ScreenWidth(); ++x)
			{
				for (int y = 0; y < ScreenHeight(); ++y)
				{
					Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
				}
			}
		}
		return true;
	}
};

int main()
{
	PixelEngine demo;
	
	if (demo.Construct(256, 240, 3, 3))
		demo.Start();


	return 0;
} 