#include "InputManager.h"
#include <windows.h>


// Singleton pattern to access InputManager globally
InputManager& InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

void InputManager::Initialize()
{
    trackedKeys.push_back('W');
    trackedKeys.push_back('S');
    trackedKeys.push_back('A');
    trackedKeys.push_back('D');
    trackedKeys.push_back(VK_LBUTTON);  // Left mouse button
    trackedKeys.push_back(VK_RETURN);   // Enter
    trackedKeys.push_back(VK_ESCAPE);   // Escape

    for (const char key : trackedKeys)
    {
        currentKeyState[key] = false;
        previousKeyState[key] = false;
        keyPressBuffer[key] = false;
    }
}

InputManager::InputManager() :
    shouldClose(false)
{
}

void InputManager::UpdateInput()
{
    if (shouldClose)
    {
        return;
    }
    for (char key : trackedKeys)
    {
        UpdateKeyState(key);
        if (IsKeyPressedOnce(key))
        {
            keyPressBuffer[key] = true;
            // Check for escape key to close the game
            if (key == VK_ESCAPE)
            {
                shouldClose = true;
            }
        }
    }
}

bool InputManager::IsKeyReleased(int keyID) const
{
    // Check if the key was previously held and is now not held
    return previousKeyState.at(keyID) && !currentKeyState.at(keyID);
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

bool InputManager::IsKeyPressedOnce(int keyID)
{
    auto currentKeyIterator = currentKeyState.find(keyID);
    auto previousKeyIterator = previousKeyState.find(keyID);

    // New press: not pressed last frame but pressed now
    if (currentKeyIterator != currentKeyState.end() && previousKeyIterator != previousKeyState.end())
    {
        bool wasPressedLastFrame = previousKeyIterator->second;
        bool isPressedNow = currentKeyIterator->second;

        if (!wasPressedLastFrame && isPressedNow)
        {
            return true;
        }
    }
    return false;
}

void InputManager::ClearKeyPressBuffers()
{
    keyPressBuffer.clear(); // Clear the buffer after processing inputs
}

bool InputManager::IsKeyPressedThisFrame(int keyID) const
{
    auto iterator = keyPressBuffer.find(keyID);
    return iterator != keyPressBuffer.end() && iterator->second;
}
