#pragma once
#include <windows.h>
#include <unordered_map>

class InputManager
{
public:
    static InputManager& Instance();

    // Movement keys
    bool IsMovingUp() const { return IsKeyHeld('W'); }
    bool IsMovingDown() const { return IsKeyHeld('S'); }
    bool IsMovingLeft() const { return IsKeyHeld('A'); }
    bool IsMovingRight() const { return IsKeyHeld('D'); }

    // Shooting (left click)
    bool IsShooting() const { return IsKeyHeld(VK_LBUTTON); }

    // Confirming (Enter key)
    bool IsConfirming() const { return IsKeyPressedOnce(VK_RETURN); }

    // Should the game close (Escape key pressed once)
    bool ShouldClose() const { return shouldClose; }

private:
    // Private constructor (singleton pattern)
    InputManager();
    void UpdateInput();

    // Tracks whether the game should close
    bool shouldClose;

    // Key state tracking
    std::unordered_map<int, bool> currentKeyState;
    std::unordered_map<int, bool> previousKeyState;

    // Update the state of a key (called for each relevant key)
    void UpdateKeyState(int vKey);

    // Check if a key is currently held down (continuous behavior)
    bool IsKeyHeld(int vKey) const;

    // Check if a key was just pressed once (transition from not pressed to pressed)
    bool IsKeyPressedOnce(int vKey) const;
};

