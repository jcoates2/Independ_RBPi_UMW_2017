#include "game_object.h"



game_object::game_object()
{
	init();
}


game_object::~game_object()
{
}

void game_object::init()
{
	xpos = ypos = xvelocity = yvelocity = mass = 0;
	angle = 90.0;  //right = 0.0, up = 90.0, left = 180.0, down = 270.0
	physics = false;
}