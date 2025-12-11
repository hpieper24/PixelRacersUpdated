//==========================================================================
// Font.h
// Author: Jody Spikes, Hailey Pieper, Ian Dudley
// Title: Pixel Font Rendering
// Description: Static font renderer for large/small text with flash effects
//==========================================================================

#ifndef FONT_H_
#define FONT_H_

#include "SDL_Plotter.h"
#include <string>

class FontRenderer {
public:
    /*
     * Description: Draw large pixel font text
     * Return: void
     * Pre-condition: SDL_Plotter g initialized, valid x,y coordinates
     * Post-condition: Large text rendered at position with optional flash
     */
    static void drawLarge(SDL_Plotter& g, int x, int y, color c, const string& text, int flashTimer = 0);

    /*
     * Description: Draw small pixel font text
     * Return: void
     * Pre-condition: SDL_Plotter g initialized, valid x,y coordinates
     * Post-condition: Small text rendered at position with optional flash
     */
    static void drawSmall(SDL_Plotter& g, int x, int y, color c, const string& text, int flashTimer = 0);
};

#endif /* FONT_H_ */
