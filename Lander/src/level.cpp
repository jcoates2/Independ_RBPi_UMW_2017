#include "level.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>



level::level(std::string path)
{
	filePath = path;
	init();
}


level::~level()
{
}

void level::init()
{
	std::ifstream readFile;
	std::string temp;
	readFile.open(filePath + "/frames.txt");

	if (readFile.is_open())
	{
		while (std::getline(readFile, temp))
		{
			temp = filePath + "/" + temp;
			addFrame(temp.c_str());
		}
	}
	else
	{
		std::cout << "Cannot open " << filePath + "/frames.txt" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}

	readFile.close();

	readFile.open(filePath + "/data.txt");

	if (readFile.is_open())
	{
		std::getline(readFile, temp);
		xpos = std::stod(temp);
		
		std::getline(readFile, temp);
		ypos = std::stod(temp);

		std::getline(readFile, temp);
		width = std::stod(temp);

		std::getline(readFile, temp);
		height = std::stod(temp);

		std::getline(readFile, temp);
		angle = std::stod(temp);

		std::getline(readFile, temp);
		lzx = std::stod(temp);

		std::getline(readFile, temp);
		lzy = std::stod(temp);

		std::getline(readFile, temp);
		lzwidth = std::stod(temp);

		std::getline(readFile, temp);
		lzheight = std::stod(temp);

		std::getline(readFile, temp);
		lzangle = std::stod(temp);

		std::getline(readFile, temp);
		gravity = std::stod(temp);

		std::getline(readFile, temp);
		name = temp;

		std::getline(readFile, temp);
		shipStartX = std::stod(temp);

		std::getline(readFile, temp);
		shipStartY = std::stod(temp);

		std::getline(readFile, temp);
		shipStartVelocityX = std::stod(temp);

		std::getline(readFile, temp);
		shipStartVelocityY = std::stod(temp);

		std::getline(readFile, temp);
		shipStartAngle = std::stod(temp);

		std::getline(readFile, temp);
		shipStartFuel = std::stod(temp);

		readFile.close();
	}
	else
	{
		std::cout << "Cannot open " << filePath + "/data.txt" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}
