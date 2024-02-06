#pragma once
#include "../../common/stdafx.h"
#include "../../common/core.h"
#include "../../common/sys.h"
#include "../../common/font.h"
#include "../../common/vector2d.h"


const unsigned int NUM_BALLS = 10;	// Max. num balls.
const float MAX_BALL_SPEED = 8.f;	// Max vel. of ball. (pixels/?).

// Textures
GLuint texbkg;
GLuint texsmallball;

/// <summary>
/// Logic Time Scale
/// </summary>
const float TIME_SCALE = 1.f;
float logicTime = 0;


// FPS variables
int framesElapsed = 0;
double time1 = 0;
double time2 = 0;
double diffTime = 0;
double FPS = 0;