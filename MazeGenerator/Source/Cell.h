#pragma once

#include <random>

struct Cell
{

	bool walls[4] = { true, true, true, true };
	bool visited = false;
	bool isEnd = false;

	Cell() = default;
	Cell(const long &x, const long &y, const long &s, const long &w, const long &h)
		: posX(x), posY(y), scale(s), width(w), height(h) { }

	void Show(sf::RenderWindow *window) const;
	void Highlight(sf::RenderWindow *window) const;
	void removeWall(Cell * next);

	Cell *getNeighbour(std::vector<Cell> &grid);
	bool isInError() const { return inError; }

private:
	bool inError = false;
	long posX = 0, posY = 0;
	long scale = 40, width = 400, height = 400;
	long locX = posX * scale, locY = posY * scale;
	long cols = static_cast<long>(std::floor(width / scale));
	long rows = static_cast<long>(std::floor(height / scale));

	long getIndex(const long &i, const long &j);
};
