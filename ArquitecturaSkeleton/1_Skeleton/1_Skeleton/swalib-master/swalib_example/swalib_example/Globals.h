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
const float TIME_SCALE = 16.f;
const double MAX_ACCUMULATED_TIME = static_cast<double>(1) / 15;

double previousTime, currentTime, elapsed, accumulatedTime = 0;
float logicTime = 0;
__int64 timestampStart = 0;
__int64 TickFrequency; // PC's tick rate
const float frameRate = static_cast<float>(1) / 60; // Cast first value or else the result is truncated -> you get 0

// FPS variables
int framesElapsed = 0;
double time1 = 0;
double time2 = 0;
double diffTime = 0;
double FPS = 0;