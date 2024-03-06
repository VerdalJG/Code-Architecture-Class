#pragma once
#include "GameManager.h"
#include "Time.h"

class Renderer
{
public:
	static Renderer& GetInstance();
	void Initialize();
	void Slot();
	void Terminate();

};


void RenderBackground();
void RenderBalls();

void InitRender()
{
	FONT_Init();	// Characters and symbols inicialization to draw on screen.

	// Set up rendering.
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Specifies clear values for the color buffers.
	glMatrixMode(GL_PROJECTION);	// Specifies projection matrix is the current matrix.
	glLoadIdentity();	// Replaces the current matrix with the identity matrix.
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);	// Multiplies the current matrix by an orthographic matrix.
	glEnable(GL_TEXTURE_2D);	// Enabling two-dimensional texturing.
	// NOTA: Mirar diferencias comentando las 2 siguientes funciones.
	glEnable(GL_BLEND);	// Blend the incoming RGBA color values with the values in the color buffers.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blend func. for alpha color.
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.

	RenderBackground();
	RenderBalls();

	// Buffers for strings below
	char FPSBuffer[50];
	char realTimeBuffer[50];
	char logicTimeBuffer[50];
	
	// Concatenate string with numbers
	snprintf(FPSBuffer, 50, "FPS: %f", FPS);
	snprintf(realTimeBuffer, 50, "RT: %f", currentTime);
	snprintf(logicTimeBuffer, 50, "LT: %f", logicTime);

	// Text
	FONT_DrawString(vec2(SCR_WIDTH - 600, SCR_HEIGHT - 50), FPSBuffer);
	FONT_DrawString(vec2(SCR_WIDTH - 600, SCR_HEIGHT - 70), realTimeBuffer);
	FONT_DrawString(vec2(SCR_WIDTH - 600, SCR_HEIGHT - 90), logicTimeBuffer);


	// Exchanges the front and back buffers
	SYS_Show();
}

void RenderBackground()
{
	// Render backgground
	for (int i = 0; i <= SCR_WIDTH / 128; i++) {
		for (int j = 0; j <= SCR_HEIGHT / 128; j++) {
			CORE_RenderCenteredSprite(vec2(i * 128.f + 64.f, j * 128.f + 64.f), vec2(128.f, 128.f), texbkg);
		}
	}
}

void RenderBalls()
{
	// Render balls
	for (int i = 0; i < NUM_BALLS; i++) {
		CORE_RenderCenteredSprite(balls[i].pos, vec2(balls[i].radius * 2.f, balls[i].radius * 2.f), balls[i].gfx);
	}
}