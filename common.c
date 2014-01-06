#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "common.h"

const float FPS = 60;
const int SCREEN_X = 640;
const int SCREEN_Y = 480;

float rotate(float r, int direction) {
	const float rotation_unit = (float)(M_PI / 16.0);
	
	r += rotation_unit * direction;
	
	return r;
}

void error(char* msg) {
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

