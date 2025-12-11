//================================================================
// Screen.cpp
// Author: Jody Spikes, Hailey Pieper, Ian Dudley
// Title: Screen Implementation
// Description: Implementation of all game UI screens
//================================================================

#include "Screen.h"

// START SCREEN

StartScreen::StartScreen() {}

void StartScreen::update() {
    flashTimer++;
}

void StartScreen::draw(SDL_Plotter& g) {
    // BACKGROUND
    for(int x = 0; x < ROW; x++) {
        for(int y = 0; y < COL; y++) {
            g.plotPixel(x, y, BG_START);
        }
    }

    // TITLE
    FontRenderer::drawLarge(g, 110, COL / 2 - 80, YELLOW, "PIXEL RACERS", 0);

    // OPTIONS
    FontRenderer::drawSmall(g, 100, COL / 2 - 15, WHITE2, "Press I for Instructions", flashTimer);
    FontRenderer::drawSmall(g, 155, COL / 2 + 15, WHITE2, "Press S to START", flashTimer);
}

bool StartScreen::handleInput(char key) {
    return (toupper(key) == 'S');
}

// INSTRUCTIONS SCREEN

InstructionsScreen::InstructionsScreen() : scrollOffset{0} {}

void InstructionsScreen::update() {
    scrollOffset++;
    if(scrollOffset > SCROLL_RESET_VALUE) {
        scrollOffset = 0;
    }
}

void InstructionsScreen::draw(SDL_Plotter& g) {
    // BACKGROUND
    for(int x = 0; x < ROW; x++) {
        for(int y = 0; y < COL; y++) {
            g.plotPixel(x, y, BG_INSTRUCTIONS);
        }
    }

    // CONTROLS HEADER
    FontRenderer::drawLarge(g, 30, 40, CYAN, "CONTROLS", 0);

    // CONTROLS INSTRUCTIONS
    FontRenderer::drawSmall(g, 30, 90, WHITE2, "UP: Accelerate", 0);
    FontRenderer::drawSmall(g, 30, 130, WHITE2, "DOWN: Brake", 0);
    FontRenderer::drawSmall(g, 30, 170, WHITE2, "LEFT/RIGHT: Steer", 0);
    FontRenderer::drawSmall(g, 30, 210, WHITE2, "Pass cars = 10pts", 0);
    FontRenderer::drawSmall(g, 30, 250, WHITE2, "Obstacles = CRASH", 0);

    // OPTIONS
    FontRenderer::drawSmall(g, 30, COL - 90, CYAN, "Press S to START", 0);
    FontRenderer::drawSmall(g, 30, COL - 130, CYAN, "Press B to go BACK", 0);
}

bool InstructionsScreen::handleInput(char key) {
    return (toupper(key) == 'I');
}

// PAUSE SCREEN

PauseScreen::PauseScreen() {}

void PauseScreen::update() {
    flashTimer++;
}

void PauseScreen::draw(SDL_Plotter& g) {
    // BACKGROUND
    for(int x = 0; x < ROW; x++) {
        for(int y = 0; y < COL; y++) {
            g.plotPixel(x, y, BG_PAUSED);
        }
    }

    // PAUSE MESSAGE
    FontRenderer::drawLarge(g, 200, COL / 2 - 30, YELLOW, "PAUSED", 0);

    // OPTIONS
    FontRenderer::drawSmall(g, 150, COL / 2 + 20, YELLOW, "Press P to Resume", flashTimer);
    FontRenderer::drawSmall(g, 140, COL / 2 + 50, CYAN, "Press B to go BACK", 0);
}

bool PauseScreen::handleInput(char key) {
    return (toupper(key) == 'P');
}

// GAME OVER SCREEN

GameOverScreen::GameOverScreen()
    : hitAI{false}, hitObstacle{false}
{}

void GameOverScreen::setGameOver(int score, bool aiHit, bool obstacleHit) {
    finalScore = score;
    hitAI = aiHit;
    hitObstacle = obstacleHit;
}

void GameOverScreen::update() {
    flashTimer++;
}

void GameOverScreen::draw(SDL_Plotter& g) {
    // BACKGROUND
    for(int x = 0; x < ROW; x++) {
        for(int y = 0; y < COL; y++) {
            g.plotPixel(x, y, BG_GAME_OVER);
        }
    }

    // GAME OVER TITLE
    FontRenderer::drawLarge(g, 150, COL / 2 - 70, RED, "GAME OVER", 0);

    // FINAL SCORE
    FontRenderer::drawSmall(g, 160, COL / 2 - 20, WHITE2, "Final Score: ", 0);
    std::string scoreStr = std::to_string(finalScore);
    FontRenderer::drawSmall(g, 360, COL / 2 - 20, WHITE2, scoreStr, 0);

    // COLLISION INFORMATION
    int yPos = COL / 2 + 10;
    if(hitAI) {
        FontRenderer::drawSmall(g, 190, yPos, AI_BLUE, "Hit AI Car!", flashTimer);
        yPos += GAME_OVER_Y_SPACING;
    }
    if(hitObstacle) {
        FontRenderer::drawSmall(g, 180, yPos, ORANGE, "Hit Obstacle!", flashTimer);
    }

    // OPTION
    FontRenderer::drawSmall(g, 140, COL - 90, WHITE2, "Press C to Restart", flashTimer);
}

bool GameOverScreen::handleInput(char key) {
    return (toupper(key) == 'C');
}

// WIN SCREEN

WinScreen::WinScreen() {}

void WinScreen::setWin(int score) {
    finalScore = score;
}

void WinScreen::update() {
    flashTimer++;
}

void WinScreen::draw(SDL_Plotter& g) {
    // BACKGROUND
    for(int x = 0; x < ROW; x++) {
        for(int y = 0; y < COL; y++) {
            g.plotPixel(x, y, BG_WIN);
        }
    }

    // WIN MESSAGE
    FontRenderer::drawLarge(g, 150, COL / 2 - 70, GREEN, "YOU WIN!", 0);

    // FINAL SCORE
    FontRenderer::drawSmall(g, 160, COL / 2 - 20, WHITE2, "Final Score: ", 0);
    std::string scoreStr = std::to_string(finalScore);
    FontRenderer::drawSmall(g, 360, COL / 2 - 20, WHITE2, scoreStr, 0);

    // OPTION
    FontRenderer::drawSmall(g, 140, COL - 90, CYAN, "Press C to Restart", flashTimer);
}

bool WinScreen::handleInput(char key) {
    return (toupper(key) == 'C');
}
