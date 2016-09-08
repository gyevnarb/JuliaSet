#include "main.h"

int main(int argc, char * argv[])
{
#ifdef DEBUG
	int ret = handleInput(argc, argv);
	system("PAUSE");
	return ret;
#else
	return handleInput(argc, argv);
#endif
}

std::string complex_to_string(const complex & parameter)
{
	return std::to_string(parameter.real()) + (parameter.imag() < 0 ? std::to_string(parameter.imag()) : "+" + std::to_string(parameter.imag())) + "i";
}

void printResult(const std::string & fn, const julia_set & js, const std::string & dest, bool & colour)
{
	std::cout << "Julia Set drawn!"
		<< "\nName: " << fn
		<< "\nResolution: " << js.getWidth() << " x " << js.getHeight()
		<< "\nParameter: " << complex_to_string(js.getParameter())
		<< "\nThreshold: " << js.getThreshold()
		<< "\nDestination: " << (dest == "" ? std::string("%(ExecutableDir)\\") + fn : dest + fn)
		<< "\nColoured: " << (colour ? "Yes" : "No") << std::endl;
}

int handleInput(int argc, char * argv[])
{
	julia_set js = julia_set(complex(-0.221, -0.713), 2.0, 1920, 1080);	///Hardcoded values of standard Julia-Set
	bool isColoured = false;
	std::string filename = "js_-0.221-0.713i.bmp", dest = "", location = filename;
	///0.378, 0.160; -0.541, 0.5; -0.830, -0.190; 0.273, 0.0

	std::cout << "Welcome to this program!\n";
	std::cout << "You can draw Julia Sets with this application!\n";
	std::cout << "By default the built in Julia Set - with parameter: -0.221-0.713i and threshold: 2.0 will be drawn!\n";
	std::cout << "Please enter \"help\" (without quotation marks) for detailed info about the usage of the program!\n";

	if (argc == 1)
	{
		bitmap::drawbmp(js.bnw_julia_set(), location.c_str(), js.getWidth(), js.getHeight());
		printResult(filename, js, dest, isColoured);
		return 0;
	}

	if (argc == 2 && std::string(argv[1]) == "help")
	{
		std::cout << "-n : Specifiy the name of the file. Usage: Julia_Set -n \"name_of_the_file\"" << std::endl;
		std::cout << "-r : Specifiy the resolution of the output. Usage: Julia_Set -r \"width\" \"height\"" << std::endl;
		std::cout << "-d: Specifiy the destination of the output file. Usage: Julia_Set -d \"destination\"" << std::endl;
		std::cout << "-p: Specifiy the complex parameter of the iteration. Usage: Julia_Set -p \"real_part\" \"imag_part\"" << std::endl;
		std::cout << "-t: Specifiy the threshold of the iteration. Usage: Julia_Set -t \"threshold\"" << std::endl;
		std::cout << "-c: Output will be coloured. Default is black-and-white. Usage: Julia_Set -c" << std::endl;
		std::cout << "-i: Specifiy the interval on which the Julia Set is evaluated. Usage: Julia_set -i -1.5 (real) -1.5 (imag)" << std::endl;
		return 0;
	}

	for (size_t i = 1; i != argc; ++i)
	{
		if (std::string(argv[i]) == "-n")
		{
			filename = argv[++i] + std::string(".bmp");
		}
		else if (std::string(argv[i]) == "-r")
		{
			js.setWidth(std::atoll(argv[++i]));
			js.setHeight(std::atoll(argv[++i]));
		}
		else if (std::string(argv[i]) == "-d")
		{
			dest = argv[++i]; 
			dest = dest[dest.size() - 1] == '\\' ? dest : dest + '\\';
		}
		else if (std::string(argv[i]) == "-p")
		{
			double first = std::atof(argv[++i]), second = std::atof(argv[++i]);
			js.setParameter(complex(first, second));
			filename = "js_" + complex_to_string(js.getParameter()) + ".bmp";
		}
		else if (std::string(argv[i]) == "-t")
		{
			js.setThreshold(std::atof(argv[++i]));
		}
		else if (std::string(argv[i]) == "-c")
		{
			isColoured = true;
		}
		else if (std::string(argv[i]) == "-i")
		{
			js.setRealIvMin(std::atof(argv[++i]));
			js.setImagIvMin(std::atof(argv[++i]));
		}
		else
		{
			std::cerr << "Invalid arguements passed!" << std::endl;
			return -1;
		}
	}

	location = dest + filename;

	if (!isColoured)
		bitmap::drawbmp(js.bnw_julia_set(), location.c_str(), js.getWidth(), js.getHeight());
	else
		bitmap::drawbmp(js.colour_julia_set(), location.c_str(), js.getWidth(), js.getHeight());

	printResult(filename, js, dest, isColoured);

	return 0;
}
