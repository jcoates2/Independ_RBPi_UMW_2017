//VERSION 0.0.4

#include "sl.h"
#include "game_object.h"
#include "level.h"
#include <string>
#include <map>
#include <iostream>
#include <thread>
#include <chrono>
#include <math.h>
#include <vector>
#include <fstream>

//---Ensure ALL locations are RELATIVE! There are still some xy-coords that are absolute and that break/look bad when the resolution is changed! GUI scaling is a MUST-HAVE!---
//Also, add an option for 4:3 screens, and make resolution configurable from some kind of main menu, along with level select, difficulty (?)< and similar options
//---UPDATE 4/10/17---
//Resolution is now locked at 1920x1080, because otherwise too much math occurs and thsi is the easy way to fix that problem
const int windowx = 1920;
const int windowy = 1080;
const int FPS = 60;  //Tell the game what framerate to run at
const double PI = 3.141592654;

double degToRad(double deg);
double radToDeg(double rad);

int main(int args, char *argv[])
{

	//Set up window and font properties
	slWindow(windowx, windowy, "Spaceship Lander - Alpha", false);
	slSetFont(slLoadFont("../ttf/white_rabbit.ttf"), 20);
	slSetTextAlign(SL_ALIGN_CENTER);



	//Load graphical assets

	//Load levels
	int currentLevel = 0;
	int numLevels = 0;

	std::string temp;
	std::vector<level> levels;

	std::ifstream readFile;
	readFile.open("../levels/levels.txt");

	if (readFile.is_open())
	{
		while (std::getline(readFile, temp))
		{
			temp = temp.substr(0, temp.length() - 1);
			std::cout << "loading " << temp << std::endl;
			level temp_level("../levels/" + temp);
			levels.push_back(temp_level);
			numLevels++;
		}
	}
	
	//Set up all kinds of useful variables
	
	bool gameOver = false;
	bool lost = false;
	bool playAgain = true;
	bool paused = false;

	game_object ship;
	ship.addFrame("../assets/spaceship.png");
	ship.addFrame("../assets/spaceship_thrust.png");
	ship.addFrame("../assets/spaceship_crash.png");
	ship.setXPos(levels[currentLevel].getShipStartX());
	ship.setYPos(levels[currentLevel].getShipStartY());
	ship.setXVelocity(levels[currentLevel].getShipStartVelocityX());
	ship.setYVelocity(levels[currentLevel].getShipStartVelocityY());
	ship.setAngle(levels[currentLevel].getShipStartAngle());
	ship.addProperty("fuel", levels[currentLevel].getShipStartFuel());
	ship.setPhysics(true);  //Currently unused, but may later be useful for applying global gravity/momentum selectively, especially in combination with custom properties
	ship.addProperty("currentFrame", 0);  //Allows the current frame to be changed as needed

	game_object outline;
	outline.addFrame("../assets/outline.png");
	outline.setXPos(960);
	outline.setYPos(540);
	
	//Font size constante, to reduce internal math
	//Fonstants?
	double fontsize1, fontsize2, fontsize3, fontsize4;
	fontsize1 = 76.8;
	fontsize2 = 38.4;
	fontsize3 = 57.6;

	while (playAgain && !slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{

		while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE) && !slGetKey(SL_KEY_ENTER) && !slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			slSetFontSize(fontsize1);
			slText(960, 720, "HOW TO PLAY");
			slSetFontSize(fontsize2);
			slText(960, 600, "Use the UP ARROW to apply thrust\n\nUse the LEFT and RIGHT ARROWS to roll\n\nPress ENTER to pause if you need a quick break\n\nLand in the red LANDING ZONE of each level to advance to the next\n\n\nPress ENTER to start!");

			slSprite(outline.getFrames()[0], outline.getXPos(), outline.getYPos(), 1920, 1080);

			slRender();

			std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
		}

		slSprite(outline.getFrames()[0], outline.getXPos(), outline.getYPos(), 1920, 1080);

		slRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		while (currentLevel != numLevels && !slGetKey(SL_KEY_ESCAPE) && !slShouldClose())
		{
			while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE) && !gameOver)
			{
				if (slGetKey(SL_KEY_ENTER))
				{
					paused = !paused;

					std::this_thread::sleep_for(std::chrono::milliseconds(5000 / FPS));
				}

				if (!paused)
				{
					if (!(ship.getYPos() <= levels[currentLevel].getYPos() + (levels[currentLevel].getHeight() / 2)))
					{
						ship.changeYVelocity(-(levels[currentLevel].getGravity() / FPS));

						//Roll left
						if (slGetKey(SL_KEY_LEFT))
						{
							ship.changeAngle(50.0 / FPS);
						}

						//Roll right
						if (slGetKey(SL_KEY_RIGHT))
						{
							ship.changeAngle(-50.0 / FPS);
						}

						if (ship.getAngle() - 90 >= 180.0)
						{
							ship.setAngle(ship.getAngle() - 360.0);
						}

						if (ship.getAngle() - 90 <= -180.0)
						{
							ship.setAngle(ship.getAngle() + 360.0);
						}
					}

					ship.changeProperty("currentFrame", 0);

					//Press the UP ARROW to go less down
					if (slGetKey(SL_KEY_UP) && ship.getProperty("fuel") > 0.0)
					{
						ship.changeYVelocity(2 * (9.8 / FPS) * sin(degToRad(ship.getAngle())));
						ship.changeXVelocity(2 * (9.8 / FPS) * roundf(100.0 * cos(degToRad(ship.getAngle()))) / 100.0);
						ship.adjustProperty("fuel", -(50.0 / FPS));
						ship.changeProperty("currentFrame", 1);
					}
					
					if (ship.getYPos() >= 1080.0)
					{
						ship.setYVelocity(0.0);
						ship.setYPos(1079.0);
					}
					
					if (ship.getYPos() <= 0.0)
					{
						ship.setYVelocity(0.0);
						ship.setYPos(1.0);
					}

					if (ship.getXPos() >= 1920.0)
					{
						ship.setXVelocity(0.0);
						ship.setXPos(1919.0);
					}
					
					if (ship.getXPos() <= 0.0)
					{
						ship.setXVelocity(0.0);
						ship.setXPos(1.0);
					}
					ship.changeYPos(ship.getYVelocity());
					ship.changeXPos(ship.getXVelocity());
				}

				slSetForeColor(1.0, 1.0, 1.0, 1.0);

				slPush();
				slTranslate(ship.getXPos(), ship.getYPos());
				slRotate(ship.getAngle() - 90);
				slSprite(ship.getFrames()[ship.getProperty("currentFrame")], 0, 0, 120, 120);
				slPop();

				slSprite(levels[currentLevel].getFrames()[0], levels[currentLevel].getXPos(), levels[currentLevel].getYPos() / 2, levels[currentLevel].getWidth(), levels[currentLevel].getHeight());

				//Indicate landing zone
				slSetForeColor(1.0, 0.0, 0.0, 0.5);
				slRectangleFill(levels[currentLevel].getLZX(), levels[currentLevel].getLZY() - (60 - levels[currentLevel].getLZHeight()), 2 * levels[currentLevel].getLZWidth(), 2 * levels[currentLevel].getLZHeight());
				slSetForeColor(1.0, 1.0, 1.0, 1.0);

				slSprite(outline.getFrames()[0], outline.getXPos(), outline.getYPos(), 1920, 1080);

				//Useful info
				slSetFontSize(fontsize2);

				slText(1622, 912, "Level:");
				slText(1766, 912, levels[currentLevel].getName().c_str());

				slText(1622, 876, "Gravity:");
				slText(1806, 876, (std::to_string(levels[currentLevel].getGravity()).substr(0, 4) + " m/s").c_str());
				/*
				slText(144, 732, "XPosition:");
				slText(288, 732, std::to_string((int)ship.getXPos()).c_str());

				slText(144, 768, "YPosition:");
				slText(288, 768, std::to_string((int)ship.getYPos()).c_str());

				slText(144, 804, "XVelocity:");
				slText(288, 804, std::to_string((int)ship.getXVelocity()).c_str());
				*/
				if (ship.getYVelocity() > -6.0)
				{
					slText(144, 840, "Delta-Y:");
					slText(288, 840, std::to_string((int)ship.getYVelocity()).c_str());
				}
				else
				{
					slSetForeColor(1.0, 0.0, 0.0, 1.0);
					slText(144, 840, "Delta-Y:");
					slText(288, 840, std::to_string((int)ship.getYVelocity()).c_str());
					slSetForeColor(1.0, 1.0, 1.0, 1.0);
				}

				if (ship.getProperty("fuel") > 20.0)
				{
					slText(144, 876, "Fuel:");
					slText(288, 876, std::to_string((int)ship.getProperty("fuel")).c_str());
				}
				else
				{
					slSetForeColor(1.0, 0.0, 0.0, 1.0);
					slText(144, 876, "Fuel:");
					slText(288, 876, std::to_string((int)ship.getProperty("fuel")).c_str());
					slSetForeColor(1.0, 1.0, 1.0, 1.0);
				}

				if (!((ship.getAngle() - 90) > levels[currentLevel].getLZAngle() + levels[currentLevel].getAngle() || (ship.getAngle() - 90) < -levels[currentLevel].getLZAngle() + levels[currentLevel].getAngle()))
				{
					slText(144, 912, "Angle:");
					slText(288, 912, std::to_string((int)ship.getAngle() - 90).c_str());
				}
				else
				{
					slSetForeColor(1.0, 0.0, 0.0, 1.0);
					slText(144, 912, "Angle:");
					slText(288, 912, std::to_string((int)ship.getAngle() - 90).c_str());
					slSetForeColor(1.0, 1.0, 1.0, 1.0);
				}
				

				if (paused)
				{
					slText(960, 540, "Paused");
				}

				//Game over conditions
				if (ship.getXPos() > levels[currentLevel].getLZX() - levels[currentLevel].getLZWidth() && ship.getXPos() < levels[currentLevel].getLZX() + levels[currentLevel].getLZWidth() && ship.getYPos() <= levels[currentLevel].getLZY() + levels[currentLevel].getLZHeight() && ship.getYPos() >= levels[currentLevel].getLZY() - levels[currentLevel].getLZHeight())
				{
					//Must land at less than 6 m/s to not crash
					//Also, cannot land tipping too far to one side
					if (ship.getYVelocity() <= -6.0 || (ship.getAngle() - 90) > levels[currentLevel].getLZAngle() + levels[currentLevel].getAngle() || (ship.getAngle() - 90) < -levels[currentLevel].getLZAngle() + levels[currentLevel].getAngle())
					{
						gameOver = true;
						lost = true;
						ship.changeProperty("currentFrame", 2);
						break;
					}
					else
					{
						ship.changeProperty("currentFrame", 0);
						gameOver = true;
						break;
					}
				}

				if (ship.getYPos() <= levels[currentLevel].getYPos() + (levels[currentLevel].getHeight() / 2))
				{
					
					if (ship.getYVelocity() <= -6.0 || (ship.getAngle() - 90) > levels[currentLevel].getLZAngle() + levels[currentLevel].getAngle() || (ship.getAngle() - 90) < -(levels[currentLevel].getLZAngle() + levels[currentLevel].getAngle()))
					{
						gameOver = true;
						lost = true;
						ship.changeProperty("currentFrame", 2);
					}
					else
					{
						ship.setXVelocity(0.0);
						ship.setYVelocity(0.0);
						ship.setAngle(90.0);
					}
					
				}

				if (ship.getYPos() <= levels[currentLevel].getYPos() + (levels[currentLevel].getHeight() / 2) && ship.getProperty("fuel") <= 0.0)
				{
					ship.setXVelocity(0.0);
					ship.setYVelocity(0.0);
					ship.setAngle(90.0);

					slText(960.0, 540.0, "You've run out of fuel! Mission failed!");
					gameOver = true;
					lost = true;
					ship.changeProperty("currentFrame", 2);

					slRender();

					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				}

				slRender();

				//Ensures game physics don't go nuts due to unlocked framerate, so locks the framerate to a predetermined value and prevents the program from running over itself
				//Sleep(1000 / FPS);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
			}

			//Ensures the rocket won't fall off the screen
			ship.setYVelocity(0.0);
			playAgain = false;

			while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
			{
				slSetForeColor(1.0, 1.0, 1.0, 1.0);
				slSprite(ship.getFrames()[ship.getProperty("currentFrame")], ship.getXPos(), ship.getYPos(), 120, 120);

				slSprite(levels[currentLevel].getFrames()[0], levels[currentLevel].getXPos(), levels[currentLevel].getYPos() / 2, levels[currentLevel].getWidth(), levels[currentLevel].getHeight());

				slSprite(outline.getFrames()[0], outline.getXPos(), outline.getYPos(), 1920, 1080);

				if (currentLevel + 1 == numLevels && !lost)
				{
					slSetFontSize(fontsize1);
					slText(960, 720, "Game Over!");

					slSetFontSize(fontsize3);
					slText(960, 600, "You landed! Well done, pilot!");
					
					slText(960, 480, "Play again? Y/N");
					if (slGetKey('Y'))
					{
						playAgain = true;
						currentLevel = 0;
						ship.setXPos(levels[currentLevel].getShipStartX());
						ship.setYPos(levels[currentLevel].getShipStartY());
						ship.setXVelocity(levels[currentLevel].getShipStartVelocityX());
						ship.setYVelocity(levels[currentLevel].getShipStartVelocityY());
						ship.setAngle(levels[currentLevel].getShipStartAngle());
						ship.changeProperty("fuel", levels[currentLevel].getShipStartFuel());
						gameOver = false;
						lost = false;
						break;
					}
				}
				else if (currentLevel + 1 != numLevels && !lost)
				{
					slSetFontSize(fontsize3);
					slText(960, 720, "You landed! Well done, pilot!");

					slText(960, 600, ("Next level: " + levels[currentLevel + 1].getName()).c_str());

					slText(960, 480, "Continue? Y/N");

					if (slGetKey('Y'))
					{
						playAgain = true;
						ship.setXPos(levels[currentLevel + 1].getShipStartX());
						ship.setYPos(levels[currentLevel + 1].getShipStartY());
						ship.setXVelocity(levels[currentLevel + 1].getShipStartVelocityX());
						ship.setYVelocity(levels[currentLevel + 1].getShipStartVelocityY());
						ship.setAngle(levels[currentLevel + 1].getShipStartAngle());
						ship.changeProperty("fuel", levels[currentLevel + 1].getShipStartFuel());
						ship.changeProperty("currentFrame", 0);
						gameOver = false;
						lost = false;
						currentLevel++;
						break;
					}
				}
				else if (lost)
				{
					slSetFontSize(fontsize1);
					slText(960, 720, "Oops!");

					slSetFontSize(fontsize3);
					slText(960, 600, "You crashed! Try again, rookie!");

					slText(960, 480, "Try again? Y/N");
					if (slGetKey('Y'))
					{
						playAgain = true;
						ship.setXPos(levels[currentLevel].getShipStartX());
						ship.setYPos(levels[currentLevel].getShipStartY());
						ship.setXVelocity(levels[currentLevel].getShipStartVelocityX());
						ship.setYVelocity(levels[currentLevel].getShipStartVelocityY());
						ship.setAngle(levels[currentLevel].getShipStartAngle());
						ship.changeProperty("fuel", levels[currentLevel].getShipStartFuel());
						ship.changeProperty("currentFrame", 0);
						gameOver = false;
						lost = false;
						break;
					}
				}

				if (slGetKey('N'))
				{
					slClose();
				}

				slRender();

				std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
			}
		}
	}

	//slClose();

	return(0);
}

double degToRad(double deg)
{
	return(deg * PI / 180);
}

double radToDeg(double rad)
{
	return(rad * 180 / PI);
}
