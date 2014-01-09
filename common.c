#include "blasteroids.h"

const float FPS = 60;
const int SCREEN_X = 640;
const int SCREEN_Y = 480;

float rotate(float heading, float direction) {
	const float rotation_unit = (float)(M_PI / 16.0);
	
	return heading + rotation_unit * direction;
}

