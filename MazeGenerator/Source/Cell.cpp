#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include "Cell.h"

void Cell::Show(sf::RenderWindow *window) const
{
	sf::VertexArray line(sf::Lines, 8);

	if (walls[0])
	{
		//Top line
		line[0].position = sf::Vector2f(locX, locY);
		line[1].position = sf::Vector2f(locX + scale, locY);
	}
	if (walls[1])
	{
		//Right line
		line[2].position = sf::Vector2f(locX + scale, locY);
		line[3].position = sf::Vector2f(locX + scale, locY + scale);
	}
	if (walls[2])
	{
		//Bottom line
		line[4].position = sf::Vector2f(locX + scale, locY + scale);
		line[5].position = sf::Vector2f(locX, locY + scale);
	}
	if (walls[3])
	{
		//Left line
		line[6].position = sf::Vector2f(locX, locY + scale);
		line[7].position = sf::Vector2f(locX, locY);
	}

	window->draw(line);

	if (visited)
	{
		sf::RectangleShape rect(sf::Vector2f(scale, scale));
		rect.setPosition(sf::Vector2f(locX, locY));
		rect.setFillColor(sf::Color());
		window->draw(rect);
	}
}

void Cell::Highlight(sf::RenderWindow *window) const
{
	if (!isEnd)
	{
		sf::RectangleShape rect(sf::Vector2f(scale, scale));
		rect.setPosition(sf::Vector2f(locX, locY));
		rect.setFillColor(sf::Color(0, 255, 0));
		window->draw(rect);
	}
	else
	{
		sf::RectangleShape rect(sf::Vector2f(scale - 6, scale - 6));
		rect.setPosition(sf::Vector2f(locX + 3, locY + 3));
		rect.setFillColor(sf::Color(255, 0, 0));
		window->draw(rect);
	}
}

long Cell::getIndex(const long & i, const long & j)
{
	if (i < 0 || j < 0 || i > cols - 1 || j > rows - 1)
	{
		return -1;
	}

	return i + j *cols;
}

Cell *Cell::getNeighbour(std::vector<Cell> &grid)
{
	std::vector<Cell> neighbours;

	//Top
	long index = getIndex(posX, posY - 1);
	if (index != -1 && !grid[index].visited) neighbours.push_back(grid[index]);

	//Right
	index = getIndex(posX + 1, posY);
	if (index != -1 && !grid[index].visited) neighbours.push_back(grid[index]);

	//Bottom
	index = getIndex(posX, posY + 1);
	if (index != -1 && !grid[index].visited) neighbours.push_back(grid[index]);

	//Left
	index = getIndex(posX - 1, posY);
	if (index != -1 && !grid[index].visited) neighbours.push_back(grid[index]);

	if (neighbours.size() > 0)
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<long> uni(0, neighbours.size() - 1);
		long rand = uni(rng);
		Cell tmp = neighbours[rand];
		return &grid[tmp.posX + tmp.posY * cols];
	}
	else
	{
		inError = true;
		return nullptr;
	}
}


void Cell::removeWall(Cell * next)
{
	if (posX - next->posX == -1)
	{
		walls[1] = false;
		next->walls[3] = false;
	}
	if (posX - next->posX == 1)
	{
		walls[3] = false;
		next->walls[1] = false;
	}
	if (posY - next->posY == -1)
	{
		walls[2] = false;
		next->walls[0] = false;
	}
	if (posY - next->posY == 1)
	{
		walls[0] = false;
		next->walls[2] = false;
	}
}
