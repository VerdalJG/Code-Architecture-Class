#pragma once
#include "GameLogic.h"

// Logic Info.
struct Ball	// Info Ball
{
	vec2   pos;	// Position.
	vec2   vel;	// Velocity.
	GLuint gfx;	// OpenGL for id. for visualization purposes. 
	float  radius;	// Radius.

	Ball() :
		pos(0.0f),
		vel(0.0f),
		gfx(0),
		radius(0.0f)
	{}
};
const unsigned int NUM_BALLS = 10;	// Max. num balls.
Ball balls[NUM_BALLS];	// Array of balls.

const float MAX_BALL_SPEED = 8.f;	// Max vel. of ball. (pixels/?).

// Textures
GLuint texbkg;
GLuint texsmallball;

double startTime;

double previousTime, currentTime, elapsed;
double PCFrequency; // PC's tick rate
double frameRate = static_cast<double>(1) / 60; // Cast first value or else the result is truncated -> you get 0

// FPS variables
int framesElapsed = 0;
double time1 = 0;
double time2 = 0;
double diffTime = 0;
double FPS = 0;