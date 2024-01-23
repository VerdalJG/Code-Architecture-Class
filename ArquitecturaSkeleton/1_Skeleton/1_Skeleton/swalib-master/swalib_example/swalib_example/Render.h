#pragma once
#include "GameUpdate.h"

void RenderBackground();
void RenderBalls();

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.

	RenderBackground();
	RenderBalls();

	// Text
	FONT_DrawString(vec2(SCR_WIDTH / 2 - 6 * 16, 16), "HELLO WORLD!");

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