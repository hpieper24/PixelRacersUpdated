//===================================================================
// main.cpp
// Author: Jody Spikes, Hailey Pieper, Ian Dudley
// Title: Pixel Racers - Main Game Loop
// Description: Main game loop handling input, updates, and rendering
//===================================================================

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include "SDL_Plotter.h"
#include "Car.h"
#include "Background.h"
#include "Collision.h"
#include "Screen.h"
#include "Points.h"
#include "Const.h"

using namespace std;

int main(int argc, char **argv) {
    // Initialize random seed
    srand((unsigned)time(0));

    // Initialize SDL and game objects
    SDL_Plotter g(ROW, COL);
    PlayerCar playerCar(PLAYER_START_X, PLAYER_START_Y, PLAYER_CAR);
    Background bg;
    PointsManager points;

    // Initialize AI cars and obstacles
    vector<AICar> aiCars = {
        AICar(LEFT_LANE_X,   -50,  AI_BLUE,  4),
        AICar(CENTER_LANE_X, -150, AI_GREEN, 3),
        AICar(RIGHT_LANE_X,  -250, AI_YELLOW,5)
    };
    vector<Obstacle> obstacles = {
        Obstacle(LEFT_LANE_X,   -100, OBSTACLE_SIZE),
        Obstacle(CENTER_LANE_X, -300, OBSTACLE_SIZE),
        Obstacle(RIGHT_LANE_X,  -500, OBSTACLE_SIZE)
    };

    // Game state management
    GameState gameState = STATE_START;
    StartScreen startScreen;
    InstructionsScreen instructionsScreen;
    PauseScreen pauseScreen;
    GameOverScreen gameOverScreen;
    WinScreen winScreen;

    int collisionCooldown = 0;
    int frameCount = 0;

    // Main game loop
    while (!g.getQuit()) {
        // Handle input
        if (g.kbhit()) {
            char c = toupper(g.getKey());

            switch (gameState) {
                case STATE_START:
                    if (c == 'I') {
                        gameState = STATE_INSTRUCTIONS;
                    } else if (startScreen.handleInput(c)) {
                        gameState = STATE_PLAYING;
                    }
                    break;

                case STATE_INSTRUCTIONS:
                    if (c == 'S')      gameState = STATE_PLAYING;
                    else if (c == 'B') gameState = STATE_START;
                    break;

                case STATE_PLAYING:
                    switch(c) {
                        case RIGHT_ARROW: playerCar.move(RIGHT_ARROW); break;
                        case LEFT_ARROW:  playerCar.move(LEFT_ARROW);  break;
                        case UP_ARROW:    playerCar.move(UP_ARROW);    break;
                        case DOWN_ARROW:  playerCar.move(DOWN_ARROW);  break;
                        case 'P':         gameState = STATE_PAUSED;    break;
                    }
                    break;

                case STATE_PAUSED:
                    if (pauseScreen.handleInput(c)) {
                        gameState = STATE_PLAYING;
                    } else if (c == 'B') {
                        gameState = STATE_START;
                    }
                    break;

                case STATE_GAME_OVER:
                    if (gameOverScreen.handleInput(c)) {
                        // Restart game
                        playerCar.respawn();
                        bg = Background();
                        points.reset();
                        collisionCooldown = 0;
                        frameCount = 0;

                        for (auto& ai : aiCars) ai.respawn();
                        for (auto& obs : obstacles) obs.respawn();

                        gameState = STATE_START;
                    }
                    break;

                case STATE_WIN:
                    if (winScreen.handleInput(c)) {
                        // Restart game
                        playerCar.respawn();
                        bg = Background();
                        points.reset();
                        collisionCooldown = 0;
                        frameCount = 0;

                        for (auto& ai : aiCars) ai.respawn();
                        for (auto& obs : obstacles) obs.respawn();

                        gameState = STATE_START;
                    }
                    break;
            }
        }

        if (g.mouseClick()) {
            g.getMouseClick(); // Clear click queue
        }

        g.clear();

        // Update and draw based on game state
        switch (gameState) {
            case STATE_START:
                startScreen.update();
                startScreen.draw(g);
                break;

            case STATE_INSTRUCTIONS:
                instructionsScreen.update();
                instructionsScreen.draw(g);
                break;

            case STATE_PAUSED:
                pauseScreen.update();
                pauseScreen.draw(g);
                break;

            case STATE_GAME_OVER:
                gameOverScreen.update();
                gameOverScreen.draw(g);
                break;

            case STATE_WIN:
                winScreen.update();
                winScreen.draw(g);
                break;

            case STATE_PLAYING: {
                // Update game logic
                bg.update(playerCar.getSpeed());
                points.updateSpeed(playerCar.getSpeed());
                points.update();
                playerCar.update(bg.getOffset()); // currently does nothing (input-driven)

                // Update AI and obstacles
                for (auto& ai : aiCars) {
                    ai.update(bg.getOffset(), obstacles);   // obstacle-aware AI
                    if (ai.isOffScreen()) {
                        ai.respawn();
                        points.addCarPass();
                    }
                }

                for (auto& obs : obstacles) {
                    obs.update(playerCar.getSpeed());
                    if (obs.isOffScreen()) {
                        obs.respawn();
                        points.addObstacleAvoided();
                    }
                }

                // Collision detection
                if (collisionCooldown <= 0) {
                    bool hitAI = false, hitObstacle = false;
                    Collision::checkAllCollisions(playerCar, aiCars, obstacles,
                                                  hitAI, hitObstacle);

                    if (hitAI || hitObstacle) {
                        playerCar.setSpeed(max(MIN_SPEED, playerCar.getSpeed() - COLLISION_SPEED_PENALTY));
                        int newScore = max(0, points.getScore() - COLLISION_POINTS_PENALTY);
                        gameOverScreen.setGameOver(newScore, hitAI, hitObstacle);
                        gameState = STATE_GAME_OVER;
                    }
                } else {
                    collisionCooldown--;
                }

                // Win condition
                if (points.getScore() >= POINTS_PER_LAP * MAX_LAPS) {
                    winScreen.setWin(points.getScore());
                    gameState = STATE_WIN;
                }

                // Draw scene
                bg.draw(g);
                for (auto& obs : obstacles) obs.draw(g);
                for (auto& ai : aiCars) ai.draw(g);
                playerCar.draw(g);

                // Draw HUD
                {
                    color hudColor(255, 255, 255);
                    string scoreStr = "Score: " + to_string(points.getScore());
                    string speedStr = "Speed: " + to_string(playerCar.getSpeed());
                    FontRenderer::drawSmall(g, 10, 20, hudColor, scoreStr, 0);
                    FontRenderer::drawSmall(g, 10, 50, hudColor, speedStr, 0);
                }

                frameCount++;
                break;
            }
        }

        g.Sleep(FRAME_DELAY_MS);
        g.update();
    }

    cout << "\n=== PIXEL RACERS ===\n";
    cout << "Final Score: " << points.getScore() << endl;
    return 0;
}
