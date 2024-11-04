#pragma once
#include <windows.h>
#include <unordered_map>



class InputManager
{
public:
    static InputManager& GetInstance();

    void Initialize();

    // Movement keys
    bool IsMovingUp() const { return IsKeyHeld('W'); }
    bool IsMovingDown() const { return IsKeyHeld('S'); }
    bool IsMovingLeft() const { return IsKeyHeld('A'); }
    bool IsMovingRight() const { return IsKeyHeld('D'); }

    bool IsUpPressed() const { return IsKeyPressedThisFrame('W'); }
    bool IsDownPressed() const { return IsKeyPressedThisFrame('S'); }
    bool IsLeftPressed() const { return IsKeyPressedThisFrame('A'); }
    bool IsRightPressed() const { return IsKeyPressedThisFrame('D'); }

    // UI keys
    bool UIMovingUp() { return IsKeyPressedThisFrame('W'); }
    bool UIMovingDown() { return IsKeyPressedThisFrame('S'); }

    // Shooting (left click)
    bool IsShooting() const { return IsKeyPressedThisFrame(VK_LBUTTON); }

    // Confirming (Enter key)
    bool IsConfirming() { return IsKeyPressedThisFrame(VK_RETURN); }

    // Should the game close (Escape key pressed once)
    bool ShouldClose() const { return shouldClose; }

    void UpdateInput();

    // Check if a key was just released (transition from pressed to not pressed)
    bool IsKeyReleased(int keyID) const;

private:
    // Private constructor (singleton pattern)
    InputManager();


    // Tracks whether the game should close
    bool shouldClose;

    // Key state tracking
    std::unordered_map<int, bool> currentKeyState;
    std::unordered_map<int, bool> previousKeyState;
    std::unordered_map<int, bool> keyPressBuffer;  // Buffer to track unprocessed key presses

    std::vector<char> trackedKeys;


    // Update the state of a key (called for each relevant key)
    void UpdateKeyState(int keyID);

public: 
    // Check if a key is currently held down (continuous behavior)
    bool IsKeyHeld(int keyID) const;

    // Check if a key was just pressed once (transition from not pressed to pressed)
    bool IsKeyPressedOnce(int keyID);

    // Clear key buffers once input is processed
    void ClearKeyPressBuffers();

    bool IsKeyPressedThisFrame(int keyID) const;
};

