#pragma once
#include "sl.h"
#include <string>
#include <vector>

class level
{
public:
	level(std::string path);
	~level();
	void init();

	double getXPos() { return(xpos); }
	void setXPos(double newXPos) { xpos = newXPos; }
	double getYPos() { return(ypos); }
	void setYPos(double newYPos) { ypos = newYPos; }

	double getWidth() { return(width); }
	void setWidth(double newWidth) { width = newWidth; };
	double getHeight() { return(height); }
	void setHeight(double newHeight) { height = newHeight; }

	double getAngle() { return(angle); }
	void setAngle(double newAngle) { angle = newAngle; }
	void adjustAngle(double AngleAdjustment) { angle += AngleAdjustment; }

	double getLZX() { return(lzx); }
	void setLZX(double newLZX) { lzx = newLZX; }
	double getLZY() { return(lzy); }
	void setLZY(double newLZY) { lzy = newLZY; }

	double getLZWidth() { return(lzwidth); }
	void setLZWidth(double newLZWidth) { lzwidth = newLZWidth; }
	double getLZHeight() { return(lzheight); }
	void setLZHeight(double newLZHeight) { lzheight = newLZHeight; }

	double getLZAngle() { return(lzangle); }
	void setLZAngle(double newLZAngle) { lzangle = newLZAngle; }
	void adjustLZAngle(double LZAngleAdjustment) { lzangle += LZAngleAdjustment; }

	double getGravity() { return(gravity); }
	void setGravity(double newGravity) { gravity = newGravity; }

	std::string getName() { return(name); }
	void setName(std::string newName) { name = newName; }

	std::vector<int> getFrames() { return(frames); }
	void addFrame(const char *filename) {
		int newFrame = slLoadTexture(filename);
		frames.push_back(newFrame);
	}

	double getShipStartX() { return(shipStartX); }
	void setShipStartX(double newShipStartX) { shipStartX = newShipStartX; }
	double getShipStartY() { return(shipStartY); }
	void setShipStartY(double newShipStartY) { shipStartY = newShipStartY; }

	double getShipStartVelocityX() { return(shipStartVelocityX); }
	void setShipStartVelocityX(double newShipStartVelocityX) { shipStartVelocityX = newShipStartVelocityX; }
	double getShipStartVelocityY() { return(shipStartVelocityY); }
	void setShipStartVelocityY(double newShipStartVelocityY) { shipStartVelocityY = newShipStartVelocityY; }

	double getShipStartAngle() { return(shipStartAngle); }
	void setShipStartAngle(double newShipStartAngle) { shipStartAngle = newShipStartAngle; }

	double getShipStartFuel() { return(shipStartFuel); }
	void setShipStartFuel(double newShipStartFuel) { shipStartFuel = newShipStartFuel; }

private:
	double xpos, ypos;
	double width, height;
	double angle;
	double lzx, lzy;
	double lzwidth, lzheight;
	double lzangle;
	double gravity;
	double shipStartX, shipStartY;
	double shipStartVelocityX, shipStartVelocityY;
	double shipStartAngle;
	double shipStartFuel;
	std::string name;
	std::string filePath;
	std::vector<int> frames;
};

