#include <SFML\Graphics.hpp>
#include <vector>
#include <stack>
#include <iostream>
#include <string>

#include "Cell.h"

#define OUT

void setupGrid(OUT std::vector<Cell> &grid, const long &rows, const long &cols, const long &scale, const long &width, const long &height);
void drawGrid(sf::RenderWindow *window, const std::vector<Cell> &grid);
bool create(const long &rows, const long &cols, const long &scale, const long &width, const long &height, const bool &screenshot);
bool takeScreenshot(const sf::RenderWindow & window);
bool run(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	return run(argc, argv);
}

bool create(const long &rows, const long &cols, const long &scale, const long &width, const long &height, const bool &screenshot)
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Maze");
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(5);

	std::vector<Cell> grid;
	setupGrid(grid, rows, cols, scale, width, height);

	Cell *current = &grid[0];
	current->visited = true;
	current->isEnd = true;

	std::stack<Cell*> stack;

	size_t max = 0;
	Cell *longest = &grid[grid.size() - 1];

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				if (screenshot && takeScreenshot(window))
					std::cout << "Saved maze to disk!" << std::endl;
				else
					std::cerr << "Didn't save maze to disk!" << std::endl;

				window.close();
			}
		}

		drawGrid(&window, grid);

		current->Highlight(&window);

		//Step 1
		Cell *next = current->getNeighbour(grid);

		if (next)
		{
			next->visited = true;

			//Step 2
			stack.push(current);

			//Step 3
			current->removeWall(next);

			//Step 4
			current = next;
		}
		else if (!stack.empty())
		{
			if (max < stack.size())
			{
				longest = current;
				max = stack.size();
			}
			current = stack.top();
			stack.pop();
		}

		longest->isEnd = true;
		longest->Highlight(&window);

		window.display();
	}

	return 0;
}

void setupGrid(OUT std::vector<Cell> &grid, const long &rows, const long &cols, const long &scale, const long &width, const long &height)
{
	for (long j = 0; j < rows; j++)
	{
		for (long i = 0; i < cols; i++)
		{
			Cell cell(i, j, scale, width, height);
			grid.push_back(cell);
		}
	}
}

void drawGrid(sf::RenderWindow *window, const std::vector<Cell> &grid)
{
	window->clear();
	for (long i = 0; i < grid.size(); i++)
	{
		grid[i].Show(window);
	}
}

bool takeScreenshot(const sf::RenderWindow & window)
{
	sf::Vector2u windowSize = window.getSize();
	sf::Texture texture;
	texture.create(windowSize.x, windowSize.y);
	texture.update(window);
	sf::Image screenshot = texture.copyToImage();
	return screenshot.saveToFile("maze.bmp");
}

bool run(int argc, char *argv[])
{
	long scale = 40, width = 400, height = 400;
	long cols = static_cast<long>(std::floor(width / scale));
	long rows = static_cast<long>(std::floor(height / scale));
	bool screenshot = false;

	std::cout << "Welcome to this maze generator program" << std::endl;
	std::cout << "If you run this program without parameters it will generate a 10 * 10 maze, where each cell is 40 pixels wide!" << std::endl;
	std::cout << "Enter \"help\" to display help" << std::endl;

	if (argc == 1)
	{
		return create(rows, cols, scale, width, height, screenshot);
	}
	else if (argc > 1)
	{
		bool displayRes = false;
		for (int arg = 1; arg < argc; arg++)
		{
			if (std::string(argv[arg]) == "help")
			{
				std::cout << "<--------------Parameters-------------->" << std::endl;
				std::cout << "-d: Create a maze with the resolution of the screen\n";
				std::cout << "-r: Specifiy custom maze resolution\n";
				std::cout << "-s: Take a screenshot at the end of generation\n";
				std::cout << "-c: Specifiy cell scale. (scale = 40px by default)" << std::endl;
				return 0;
			}
			else if (std::string(argv[arg]) == "-d")
			{
				sf::VideoMode vm = sf::VideoMode::getDesktopMode();
				width = vm.width; height = vm.height;
				cols = static_cast<long>(std::floor(width / scale));
				rows = static_cast<long>(std::floor(height / scale));
				displayRes = true;
			}
			else if (std::string(argv[arg]) == "-r")
			{
				if (!displayRes)
				{
					width = std::stoi(std::string(argv[++arg]));
					height = std::stoi(std::string(argv[++arg]));
					cols = static_cast<long>(std::floor(width / scale));
					rows = static_cast<long>(std::floor(height / scale));
				}
				else
				{
					std::cerr << "Cannot use -d and -r at the same time! Maze will be generated with the screen resolution!" << std::endl;
				}
			}
			else if (std::string(argv[arg]) == "-s")
			{
				screenshot = true;
			}
			else if (std::string(argv[arg]) == "-c")
			{
				scale = std::stoi(std::string(argv[++arg]));
				cols = static_cast<long>(std::floor(width / scale));
				rows = static_cast<long>(std::floor(height / scale));
			}
			else
			{
				std::cerr << "Invalid arguments passed!" << std::endl;
				return -1;
			}
		}
	}
	else
	{
		std::cerr << "Invalid arguments passed!" << std::endl;
		return -1;
	}

	return create(rows, cols, scale, width, height, screenshot);
}
