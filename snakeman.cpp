#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int tailX[35], tailY[35];
int nTail;

class Game
{
public:
	Game()
	{}
	~Game()
	{}
void Sound()
{
	Beep(523.251, 700);
	Beep(523.251, 600);
	Beep(523.251, 500);
}
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
	{
		std::cout << "#";
	}
	std::cout << endl;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				std::cout << "#";
			}
			if (i == y && j == x)
			{
				std::cout << "O";
			}
			else if (i == fruitY && j == fruitX)
			{
				std::cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						std::cout << "o";
						print = true;
					}
				}
				if (!print)
				{
					std::cout << " ";
				}
			}
			if (j == width - 1)
			{
				std::cout << "#";
			}
		}
		std::cout << endl;
	}
	for (int i = 0; i < width + 2; i++)
	{
		std::cout << "#";
	}
	std::cout << endl;
	std::cout << "Score: " << score << endl;
}
void Input()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		dir = LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		dir = RIGHT;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		dir = UP;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		dir = DOWN;
	}
	if (_kbhit())
		switch (_getch())
		{
		case 'x':
			gameOver = true;
			break;
		}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	if (y >= height)
	{
		y = 0;
	}
	else if (y < 0)
	{
		y = height - 1;
	}
	if (x >= width)
	{
		x = 0;
	}

	else if (x < 0)
	{
		x = width - 1;
	}
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
			std::cout << "Game Over" << endl;
			Sound();
		}
	}
	
	if (x == fruitX && y == fruitY)
	{
		score += 5;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

};
int main()
{
	Game *game = new Game();
	game->Setup();
	while(!gameOver)
	{
		game->Draw();
		game->Input();
		game->Logic();
	}
	return 0;
}
