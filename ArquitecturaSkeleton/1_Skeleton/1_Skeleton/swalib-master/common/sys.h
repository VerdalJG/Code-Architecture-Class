#ifndef _SYS_H_
#define _SYS_H_

// Window constants
#define SCR_WIDTH  640
#define SCR_HEIGHT 480
#define SCR_FULLSCREEN 0

//#############################################################################
#ifdef _WIN32
//#############################################################################
// Keyboard constants
#define SYS_KEY_UP    VK_UP
#define SYS_KEY_DOWN  VK_DOWN
#define SYS_KEY_LEFT  VK_LEFT
#define SYS_KEY_RIGHT VK_RIGHT

#define SYS_MB_LEFT   VK_LBUTTON
#define SYS_MB_RIGHT  VK_RBUTTON
#define SYS_MB_MIDDLE VK_MBUTTON

//#############################################################################
#elif defined(__APPLE__)
#include "TargetConditionals.h"
#if defined(__MACH__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
//#############################################################################

#define SYS_KEY_UP    GLFW_KEY_UP
#define SYS_KEY_DOWN  GLFW_KEY_DOWN
#define SYS_KEY_LEFT  GLFW_KEY_LEFT
#define SYS_KEY_RIGHT GLFW_KEY_RIGHT

#define SYS_MB_LEFT   GLFW_MOUSE_BUTTON_LEFT
#define SYS_MB_RIGHT  GLFW_MOUSE_BUTTON_RIGHT
#define SYS_MB_MIDDLE GLFW_MOUSE_BUTTON_MIDDLE

#endif
#endif

struct ivec2 { int x, y; };

//-----------------------------------------------------------------------------
// Process Windows OS messages
void  SYS_Pump      ();
//-----------------------------------------------------------------------------
// Swap buffers to show on screen.
void  SYS_Show      ();
//-----------------------------------------------------------------------------
// True if there is a Windows OS message to exit.
bool  SYS_GottaQuit ();
//-----------------------------------------------------------------------------
// Stop process execution.
// ms -	Milliseconds stopped.
void  SYS_Sleep     (int ms);
//-----------------------------------------------------------------------------
// True if a key is pressed.
bool  SYS_KeyPressed       (int key);
//-----------------------------------------------------------------------------
// Retrieve mouse position on windows.
ivec2 SYS_MousePos         ();
//-----------------------------------------------------------------------------
// True if button mouse is pressed.
bool  SYS_MouseButonPressed(int button);

void SYS_Quit();


#endif
