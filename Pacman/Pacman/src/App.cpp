#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

double diffTime(clock_t start, clock_t end)
{
	double diff = end - start;
	diff /= CLOCKS_PER_SEC/1000.;
	return diff;
}

class PLAYER
{
private:

	std::wstring m_allSprites = L"UC∩Ɔ";

public:
	wchar_t m_sprite;
	const std::wstring& cmap;
	const int screenWidth, screenHeight;
	unsigned int m_x, m_y;
	enum Direction { TOP = 0, RIGHT, BOTTOM, LEFT };
	clock_t m_lastAction;

	PLAYER(const std::wstring &map, int width, int height) : m_x(10), m_y(5), m_sprite(m_allSprites[Direction::RIGHT]), cmap(map), screenWidth(width), screenHeight(height)
	{
		m_lastAction=clock();
	}

	void move(char dir)
	{
		switch (dir)
		{
		case 'W':
			m_sprite = m_allSprites[Direction::TOP];
			if (cmap[(m_y-1) * screenWidth + m_x] != '#'  && diffTime(m_lastAction, clock())>300)
			{
				m_y--;
				m_lastAction = clock();
			}
			break;
		case 'S':
			m_sprite = m_allSprites[Direction::BOTTOM];
			if (cmap[(m_y+1) * screenWidth + m_x] != '#' && diffTime(m_lastAction, clock()) > 300)
			{
				m_y++;
				m_lastAction = clock();
			}
			break;
		case 'A':
			m_sprite = m_allSprites[Direction::LEFT];
			if (cmap[m_y * screenWidth + m_x-1] != '#' && diffTime(m_lastAction, clock()) > 300)
			{
				m_x--;
				m_lastAction = clock();
			}
			break;
		case 'D':
			m_sprite = m_allSprites[Direction::RIGHT];
			if (cmap[m_y * screenWidth + m_x+1] != '#' && diffTime(m_lastAction, clock()) > 300)
			{
				m_x++;
				m_lastAction = clock();
			}
			break;

		}
	}



};


class MAP
{
	friend class PLAYER;
private:
	const std::wstring m_cmap;
	std::wstring m_workMap;
	const int screenWidth, screenHeight;
	HANDLE hConsoleScreenBuffer;
	DWORD dwBytesWritten = 0;
	PLAYER pacman;

public:
	MAP(std::wstring map, HANDLE ConsoleScreenBufferHandle, const int& width, const int& height) :
		m_cmap(map), m_workMap(map), hConsoleScreenBuffer(ConsoleScreenBufferHandle), screenWidth(width), screenHeight(height), pacman(m_cmap,width,height)
	{

	}

	void drawMap()
	{
		
		m_workMap = m_cmap;
		m_workMap[pacman.m_y * screenWidth + pacman.m_x] = pacman.m_sprite;
		WriteConsoleOutputCharacterW(hConsoleScreenBuffer, m_workMap.c_str(), screenHeight * screenWidth + 1, { 0,0 }, &dwBytesWritten);
	}

	void drawClearMap()
	{
		WriteConsoleOutputCharacterW(hConsoleScreenBuffer, m_cmap.c_str(), screenHeight * screenWidth + 1, { 0,0 }, &dwBytesWritten);

	}

	void characterMovement()
	{
		if (GetAsyncKeyState('W'))
		{
			pacman.move('W');
		}
		else if (GetAsyncKeyState('S'))
		{
			pacman.move('S');
		}
		else if (GetAsyncKeyState('A'))
		{
			pacman.move('A');
		}
		else if (GetAsyncKeyState('D'))
		{
			pacman.move('D');
		}
	}
};









int main()
{
	int screenWidth = 20;
	int screenHeight = 10;

	SetConsoleTitle("PACMAN MK I");
	HANDLE hConsoleScreenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleActiveScreenBuffer(hConsoleScreenBuffer);
	

	
	

	DWORD dwBytesWritten = 0;

	std::wstring refMap;
	refMap += L"####################";
	refMap += L"#                  #";
	refMap += L"#     #       #    #";
	refMap += L"#     #       #    #";
	refMap += L"#     #       #    #";
	refMap += L"#                  #";
	refMap += L"#                  #";
	refMap += L"#       #####      #";
	refMap += L"#                  #";
	refMap += L"####################";



	MAP map(refMap, hConsoleScreenBuffer, screenWidth, screenHeight);



	while(true)
	{
		map.characterMovement();
		map.drawMap();
	}
	

	return 0;
}