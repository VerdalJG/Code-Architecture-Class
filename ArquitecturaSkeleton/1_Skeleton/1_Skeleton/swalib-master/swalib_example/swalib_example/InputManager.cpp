#include "InputManager.h"
#include <windows.h>


// Singleton pattern to access InputManager globally
InputManager& InputManager::Instance()
{
    static InputManager instance;
    return instance;
}

InputManager::InputManager() :
    shouldClose(false)
{
}

void InputManager::UpdateInput()
{
    // Update the current state of each key we care about
    UpdateKeyState('W');
    UpdateKeyState('A');
    UpdateKeyState('S');
    UpdateKeyState('D');
    UpdateKeyState(VK_LBUTTON);   // Left mouse button
    UpdateKeyState(VK_ESCAPE);    // Escape
    UpdateKeyState(VK_RETURN);    // Enter

    // Check for escape key to close the game
    if (IsKeyPressedOnce(VK_ESCAPE)) 
    {
        shouldClose = true;
    }
}

void InputManager::UpdateKeyState(int keyID)
{
    previousKeyState[keyID] = currentKeyState[keyID];
    currentKeyState[keyID] = (GetAsyncKeyState(keyID) & 0x8000) != 0;
}

bool InputManager::IsKeyHeld(int keyID) const
{
    auto iterator = currentKeyState.find(keyID);
    return iterator != currentKeyState.end() && iterator->second;
}

bool InputManager::IsKeyPressedOnce(int keyID) const
{
    auto currentKeyIterator = currentKeyState.find(keyID);
    auto previousKeyIterator = previousKeyState.find(keyID);

    if (currentKeyIterator != currentKeyState.end() && previousKeyIterator != previousKeyState.end()) 
    {
        // Return true if it was not pressed last frame but is pressed now
        return !previousKeyIterator->second && currentKeyIterator->second;
    }
    return false;
}
