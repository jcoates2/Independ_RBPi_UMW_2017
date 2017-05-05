#pragma once
#include "sl.h"
#include <vector>
#include <map>
#include <string>

class game_object
{
public:
	game_object();
	~game_object();
	void init();

	double getXPos() { return(xpos); }
	void setXPos(double newXPos) { xpos = newXPos; }
	void changeXPos(double xAdjustment) { xpos += xAdjustment; }

	double getYPos() { return(ypos); }
	void setYPos(double newYPos) { ypos = newYPos; }
	void changeYPos(double yAdjustment) { ypos += yAdjustment; }

	double getXVelocity() { return(xvelocity); }
	void setXVelocity(double newXVelocity) { xvelocity = newXVelocity; }
	void changeXVelocity(double xAdjustment) { xvelocity += xAdjustment; }

	double getYVelocity() { return(yvelocity); }
	void setYVelocity(double newYVelocity) { yvelocity = newYVelocity; }
	void changeYVelocity(double yAdjustment) { yvelocity += yAdjustment; }

	double getAngle() { return(angle); }
	void setAngle(double newAngle) { angle = newAngle; }
	void changeAngle(double angleAdjustment) { angle += angleAdjustment; }

	double getMass() { return(mass); }
	void setMass(double newMass) { mass = newMass; }

	bool getPhysics() { return(physics); }
	void setPhysics(bool newPhysics) { physics = newPhysics; }

	std::vector<int> getFrames() { return(frames); }
	void addFrame(const char *filename) {
		int newFrame = slLoadTexture(filename);
		frames.push_back(newFrame);
	}

	std::map<std::string, double> getProperties() { return(properties); }
	double getProperty(std::string p) {
		if (properties[p] != NULL)
		{
			return(properties[p]);
		}
		return(NULL);
	}
	void adjustProperty(std::string name, double value) {
		double temp = properties[name];
		properties[name] = (temp += value);
	}
	void changeProperty(std::string name, double value) {
		properties[name] = value;
	}
	void addProperty(std::string name, double value) {
		properties[name] = value;
	}

private:
	double xpos, ypos;
	double xvelocity, yvelocity;
	double angle;
	double mass;
	bool physics;
	std::vector<int> frames;
	std::map<std::string, double> properties;
};

