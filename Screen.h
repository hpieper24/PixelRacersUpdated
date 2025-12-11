//===============================================
// Screen.h
// Author: Jody Spikes, Hailey Pieper, Ian Dudley
// Title: Screen Classes
// Description: UI screens for game states
//===============================================

#ifndef Screen_h
#define Screen_h

#include "Const.h"
#include "Font.h"

// BASE SCREEN CLASS
class Screen {
protected:
    int finalScore; // Final player score
    int flashTimer; // Timer for flashing text effects

public:
    /*
     * Description: Initialize screen with default values
     * Return: None (constructor)
     * Pre-condition: None
     * Post-condition: Screen created with finalScore = 0, flashTimer = 0
     */
    Screen() : finalScore{0}, flashTimer{0} {}

    /*
     * Description: Update screen state
     * Return: void
     * Pre-condition: None
     * Post-condition: Screen state updated
     */
    virtual void update() = 0;

    /*
     * Description: Draw screen to display
     * Return: void
     * Pre-condition: SDL_Plotter g is initialized
     * Post-condition: Screen rendered to plotter
     */
    virtual void draw(SDL_Plotter& g) = 0;

    /*
     * Description: Handle keyboard input for screen
     * Return: bool - true if transition triggered, false otherwise
     * Pre-condition: key is valid
     * Post-condition: Input processed, possible state change
     */
    virtual bool handleInput(char key) = 0;

    /*
     * Description: Virtual destructor
     * Return: None (destructor)
     * Pre-condition: None
     * Post-condition: Properly deallocate derived class resources
     */
    virtual ~Screen() {}
};

// START SCREEN
class StartScreen : public Screen {
public:
    /*
     * Description: Initialize start screen
     * Return: None (constructor)
     * Pre-condition: None
     * Post-condition: StartScreen created with flashTimer = 0
     */
    StartScreen();

    /*
     * Description: Update start screen animations
     * Return: void
     * Pre-condition: None
     * Post-condition: flashTimer incremented
     */
    void update() override;

    /*
     * Description: Draw start screen with title and instructions
     * Return: void
     * Pre-condition: SDL_Plotter g is initialized
     * Post-condition: Start screen rendered to plotter
     */
    void draw(SDL_Plotter& g) override;

    /*
     * Description: Handle start screen input (S to start game)
     * Return: bool - true if S pressed, false otherwise
     * Pre-condition: key is valid
     * Post-condition: Input processed, no state change to screen
     */
    bool handleInput(char key) override;
};

// INSTRUCTIONS SCREEN
class InstructionsScreen : public Screen {
private:
    int scrollOffset; // Offset for scrolling animation

public:
    /*
     * Description: Initialize instructions screen
     * Return: None (constructor)
     * Pre-condition: None
     * Post-condition: InstructionsScreen created with scrollOffset = 0
     */
    InstructionsScreen();

    /*
     * Description: Update instructions screen scroll animation
     * Return: void
     * Pre-condition: None
     * Post-condition: scrollOffset incremented and wrapped
     */
    void update() override;

    /*
     * Description: Draw instructions screen with controls guide
     * Return: void
     * Pre-condition: SDL_Plotter g is initialized
     * Post-condition: Instructions screen rendered to plotter
     */
    void draw(SDL_Plotter& g) override;

    /*
     * Description: Handle instructions screen input (I to go back)
     * Return: bool - true if I pressed, false otherwise
     * Pre-condition: key is valid
     * Post-condition: Input processed, no state change to screen
     */
    bool handleInput(char key) override;
};

// PAUSE SCREEN
class PauseScreen : public Screen {
public:
    /*
     * Description: Initialize pause screen
     * Return: None (constructor)
     * Pre-condition: None
     * Post-condition: PauseScreen created with flashTimer = 0
     */
    PauseScreen();

    /*
     * Description: Update pause screen animations
     * Return: void
     * Pre-condition: None
     * Post-condition: flashTimer incremented
     */
    void update() override;

    /*
     * Description: Draw pause screen with message and options
     * Return: void
     * Pre-condition: SDL_Plotter g is initialized
     * Post-condition: Pause screen rendered to plotter
     */
    void draw(SDL_Plotter& g) override;

    /*
     * Description: Handle pause screen input (P to resume game)
     * Return: bool - true if P pressed, false otherwise
     * Pre-condition: key is valid
     * Post-condition: Input processed, no state change to screen
     */
    bool handleInput(char key) override;
};

// GAME OVER SCREEN
class GameOverScreen : public Screen {
private:
    bool hitAI;			// Whether collision was with AI
    bool hitObstacle;	// Whether collision was with obstacle

public:
    /*
     * Description: Initialize game over screen
     * Return: None (constructor)
     * Pre-condition: None
     * Post-condition: GameOverScreen created with collision flags false
     */
    GameOverScreen();

    /*
     * Description: Set game over condition and final score
     * Return: void
     * Pre-condition: score >= 0, aiHit and obstacleHit are valid
     * Post-condition: Game over state set with provided values
     */
    void setGameOver(int score, bool aiHit, bool obstacleHit);

    /*
     * Description: Update game over screen animations
     * Return: void
     * Pre-condition: None
     * Post-condition: flashTimer incremented
     */
    void update() override;

    /*
     * Description: Draw game over screen with score and collision info
     * Return: void
     * Pre-condition: SDL_Plotter g is initialized
     * Post-condition: Game over screen rendered to plotter
     */
    void draw(SDL_Plotter& g) override;

    /*
     * Description: Handle game over screen input (C to restart)
     * Return: bool - true if C pressed, false otherwise
     * Pre-condition: key is valid
     * Post-condition: Input processed, no state change to screen
     */
    bool handleInput(char key) override;
};

// WIN SCREEN
class WinScreen : public Screen {
public:
    /*
     * Description: Initialize win screen
     * Return: None (constructor)
     * Pre-condition: None
     * Post-condition: WinScreen created with default values
     */
    WinScreen();

    /*
     * Description: Set win condition and final score
     * Return: void
     * Pre-condition: score >= 0
     * Post-condition: Win state set with score, collision flags reset
     */
    void setWin(int score);

    /*
     * Description: Update win screen animations
     * Return: void
     * Pre-condition: None
     * Post-condition: flashTimer incremented
     */
    void update() override;

    /*
     * Description: Draw win screen with victory message and score
     * Return: void
     * Pre-condition: SDL_Plotter g is initialized
     * Post-condition: Win screen rendered to plotter
     */
    void draw(SDL_Plotter& g) override;

    /*
     * Description: Handle win screen input (C to restart)
     * Return: bool - true if C pressed, false otherwise
     * Pre-condition: key is valid
     * Post-condition: Input processed, no state change to screen
     */
    bool handleInput(char key) override;
};

#endif /* Screen_h */
